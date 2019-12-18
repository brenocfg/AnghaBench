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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 unsigned char NSP_DISCINIT ; 
 scalar_t__ cpu_to_le16 (unsigned short) ; 
 struct sk_buff* dn_alloc_skb (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int /*<<< orphan*/ ,struct dst_entry*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static __inline__ void dn_nsp_do_disc(struct sock *sk, unsigned char msgflg,
			unsigned short reason, gfp_t gfp,
			struct dst_entry *dst,
			int ddl, unsigned char *dd, __le16 rem, __le16 loc)
{
	struct sk_buff *skb = NULL;
	int size = 7 + ddl + ((msgflg == NSP_DISCINIT) ? 1 : 0);
	unsigned char *msg;

	if ((dst == NULL) || (rem == 0)) {
		net_dbg_ratelimited("DECnet: dn_nsp_do_disc: BUG! Please report this to SteveW@ACM.org rem=%u dst=%p\n",
				    le16_to_cpu(rem), dst);
		return;
	}

	if ((skb = dn_alloc_skb(sk, size, gfp)) == NULL)
		return;

	msg = skb_put(skb, size);
	*msg++ = msgflg;
	*(__le16 *)msg = rem;
	msg += 2;
	*(__le16 *)msg = loc;
	msg += 2;
	*(__le16 *)msg = cpu_to_le16(reason);
	msg += 2;
	if (msgflg == NSP_DISCINIT)
		*msg++ = ddl;

	if (ddl) {
		memcpy(msg, dd, ddl);
	}

	/*
	 * This doesn't go via the dn_nsp_send() function since we need
	 * to be able to send disc packets out which have no socket
	 * associations.
	 */
	skb_dst_set(skb, dst_clone(dst));
	dst_output(&init_net, skb->sk, skb);
}