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
struct xfrm_policy {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; scalar_t__ sadb_msg_errno; scalar_t__ sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ) ; 
 int pfkey_xfrm_policy2msg (struct sk_buff*,struct xfrm_policy*,int) ; 
 struct sk_buff* pfkey_xfrm_policy2msg_prep (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int key_pol_get_resp(struct sock *sk, struct xfrm_policy *xp, const struct sadb_msg *hdr, int dir)
{
	int err;
	struct sk_buff *out_skb;
	struct sadb_msg *out_hdr;
	err = 0;

	out_skb = pfkey_xfrm_policy2msg_prep(xp);
	if (IS_ERR(out_skb)) {
		err =  PTR_ERR(out_skb);
		goto out;
	}
	err = pfkey_xfrm_policy2msg(out_skb, xp, dir);
	if (err < 0) {
		kfree_skb(out_skb);
		goto out;
	}

	out_hdr = (struct sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = hdr->sadb_msg_version;
	out_hdr->sadb_msg_type = hdr->sadb_msg_type;
	out_hdr->sadb_msg_satype = 0;
	out_hdr->sadb_msg_errno = 0;
	out_hdr->sadb_msg_seq = hdr->sadb_msg_seq;
	out_hdr->sadb_msg_pid = hdr->sadb_msg_pid;
	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_ONE, sk, xp_net(xp));
	err = 0;

out:
	return err;
}