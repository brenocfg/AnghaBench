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
typedef  int /*<<< orphan*/  u16 ;
struct l2tp_tunnel {scalar_t__ encap; } ;
struct l2tp_session {int peer_session_id; scalar_t__ l2specific_type; int ns; int /*<<< orphan*/  name; scalar_t__ send_seq; int /*<<< orphan*/  cookie_len; int /*<<< orphan*/ * cookie; struct l2tp_tunnel* tunnel; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ L2TP_ENCAPTYPE_UDP ; 
 int /*<<< orphan*/  L2TP_HDR_VER_3 ; 
 scalar_t__ L2TP_L2SPECTYPE_DEFAULT ; 
 int /*<<< orphan*/  L2TP_MSG_SEQ ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_dbg (struct l2tp_session*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_build_l2tpv3_header(struct l2tp_session *session, void *buf)
{
	struct l2tp_tunnel *tunnel = session->tunnel;
	char *bufp = buf;
	char *optr = bufp;

	/* Setup L2TP header. The header differs slightly for UDP and
	 * IP encapsulations. For UDP, there is 4 bytes of flags.
	 */
	if (tunnel->encap == L2TP_ENCAPTYPE_UDP) {
		u16 flags = L2TP_HDR_VER_3;
		*((__be16 *) bufp) = htons(flags);
		bufp += 2;
		*((__be16 *) bufp) = 0;
		bufp += 2;
	}

	*((__be32 *) bufp) = htonl(session->peer_session_id);
	bufp += 4;
	if (session->cookie_len) {
		memcpy(bufp, &session->cookie[0], session->cookie_len);
		bufp += session->cookie_len;
	}
	if (session->l2specific_type == L2TP_L2SPECTYPE_DEFAULT) {
		u32 l2h = 0;

		if (session->send_seq) {
			l2h = 0x40000000 | session->ns;
			session->ns++;
			session->ns &= 0xffffff;
			l2tp_dbg(session, L2TP_MSG_SEQ,
				 "%s: updated ns to %u\n",
				 session->name, session->ns);
		}

		*((__be32 *)bufp) = htonl(l2h);
		bufp += 4;
	}

	return bufp - optr;
}