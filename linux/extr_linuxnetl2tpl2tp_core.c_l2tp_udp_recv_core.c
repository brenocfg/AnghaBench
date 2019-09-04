#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct udphdr {int dummy; } ;
struct sk_buff {int len; unsigned char* data; } ;
struct l2tp_tunnel {int debug; int version; int tunnel_id; int /*<<< orphan*/  name; } ;
struct l2tp_session {int /*<<< orphan*/  recv_skb; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int L2TP_HDRFLAG_L ; 
 int L2TP_HDRFLAG_T ; 
 int L2TP_HDR_SIZE_MAX ; 
 int L2TP_HDR_VER_2 ; 
 int L2TP_HDR_VER_3 ; 
 int L2TP_HDR_VER_MASK ; 
 int L2TP_MSG_DATA ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  l2tp_dbg (struct l2tp_tunnel*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l2tp_info (struct l2tp_tunnel*,int,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  l2tp_recv_common (struct l2tp_session*,struct sk_buff*,unsigned char*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 struct l2tp_session* l2tp_tunnel_get_session (struct l2tp_tunnel*,int) ; 
 scalar_t__ l2tp_v3_ensure_opt_in_linear (struct l2tp_session*,struct sk_buff*,unsigned char**,unsigned char**) ; 
 int min (unsigned int,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int l2tp_udp_recv_core(struct l2tp_tunnel *tunnel, struct sk_buff *skb)
{
	struct l2tp_session *session = NULL;
	unsigned char *ptr, *optr;
	u16 hdrflags;
	u32 tunnel_id, session_id;
	u16 version;
	int length;

	/* UDP has verifed checksum */

	/* UDP always verifies the packet length. */
	__skb_pull(skb, sizeof(struct udphdr));

	/* Short packet? */
	if (!pskb_may_pull(skb, L2TP_HDR_SIZE_MAX)) {
		l2tp_info(tunnel, L2TP_MSG_DATA,
			  "%s: recv short packet (len=%d)\n",
			  tunnel->name, skb->len);
		goto error;
	}

	/* Trace packet contents, if enabled */
	if (tunnel->debug & L2TP_MSG_DATA) {
		length = min(32u, skb->len);
		if (!pskb_may_pull(skb, length))
			goto error;

		pr_debug("%s: recv\n", tunnel->name);
		print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, skb->data, length);
	}

	/* Point to L2TP header */
	optr = ptr = skb->data;

	/* Get L2TP header flags */
	hdrflags = ntohs(*(__be16 *) ptr);

	/* Check protocol version */
	version = hdrflags & L2TP_HDR_VER_MASK;
	if (version != tunnel->version) {
		l2tp_info(tunnel, L2TP_MSG_DATA,
			  "%s: recv protocol version mismatch: got %d expected %d\n",
			  tunnel->name, version, tunnel->version);
		goto error;
	}

	/* Get length of L2TP packet */
	length = skb->len;

	/* If type is control packet, it is handled by userspace. */
	if (hdrflags & L2TP_HDRFLAG_T) {
		l2tp_dbg(tunnel, L2TP_MSG_DATA,
			 "%s: recv control packet, len=%d\n",
			 tunnel->name, length);
		goto error;
	}

	/* Skip flags */
	ptr += 2;

	if (tunnel->version == L2TP_HDR_VER_2) {
		/* If length is present, skip it */
		if (hdrflags & L2TP_HDRFLAG_L)
			ptr += 2;

		/* Extract tunnel and session ID */
		tunnel_id = ntohs(*(__be16 *) ptr);
		ptr += 2;
		session_id = ntohs(*(__be16 *) ptr);
		ptr += 2;
	} else {
		ptr += 2;	/* skip reserved bits */
		tunnel_id = tunnel->tunnel_id;
		session_id = ntohl(*(__be32 *) ptr);
		ptr += 4;
	}

	/* Find the session context */
	session = l2tp_tunnel_get_session(tunnel, session_id);
	if (!session || !session->recv_skb) {
		if (session)
			l2tp_session_dec_refcount(session);

		/* Not found? Pass to userspace to deal with */
		l2tp_info(tunnel, L2TP_MSG_DATA,
			  "%s: no session found (%u/%u). Passing up.\n",
			  tunnel->name, tunnel_id, session_id);
		goto error;
	}

	if (tunnel->version == L2TP_HDR_VER_3 &&
	    l2tp_v3_ensure_opt_in_linear(session, skb, &ptr, &optr))
		goto error;

	l2tp_recv_common(session, skb, ptr, optr, hdrflags, length);
	l2tp_session_dec_refcount(session);

	return 0;

error:
	/* Put UDP header back */
	__skb_push(skb, sizeof(struct udphdr));

	return 1;
}