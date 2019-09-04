#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_user_sec_ctx {int dummy; } ;
struct xfrm_selector {void* dport_mask; scalar_t__ dport; void* proto; int /*<<< orphan*/  prefixlen_d; int /*<<< orphan*/  daddr; void* sport_mask; scalar_t__ sport; int /*<<< orphan*/  prefixlen_s; int /*<<< orphan*/  saddr; int /*<<< orphan*/  family; } ;
struct xfrm_sec_ctx {int dummy; } ;
struct xfrm_policy {int dummy; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_x_sec_ctx {int dummy; } ;
struct sadb_x_policy {scalar_t__ sadb_x_policy_dir; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; } ;
struct sadb_address {int /*<<< orphan*/  sadb_address_proto; int /*<<< orphan*/  sadb_address_prefixlen; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ byid; } ;
struct km_event {int /*<<< orphan*/  event; TYPE_1__ data; int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  sel ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_MARK ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPSEC_DIR_MAX ; 
 int SADB_EXT_ADDRESS_DST ; 
 int SADB_EXT_ADDRESS_SRC ; 
 int SADB_X_EXT_POLICY ; 
 int SADB_X_EXT_SEC_CTX ; 
 int /*<<< orphan*/  XFRM_MSG_DELPOLICY ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 void* htons (int) ; 
 int /*<<< orphan*/  kfree (struct xfrm_user_sec_ctx*) ; 
 int /*<<< orphan*/  km_policy_notify (struct xfrm_policy*,scalar_t__,struct km_event*) ; 
 int /*<<< orphan*/  memset (struct xfrm_selector*,int /*<<< orphan*/ ,int) ; 
 void* pfkey_proto_to_xfrm (int /*<<< orphan*/ ) ; 
 struct xfrm_user_sec_ctx* pfkey_sadb2xfrm_user_sec_ctx (struct sadb_x_sec_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_sadb_addr2xfrm_addr (struct sadb_address*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  present_and_same_family (void* const,void* const) ; 
 int security_xfrm_policy_alloc (struct xfrm_sec_ctx**,struct xfrm_user_sec_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_xfrm_policy_free (struct xfrm_sec_ctx*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  xfrm_audit_policy_delete (struct xfrm_policy*,int,int) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_bysel_ctx (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct xfrm_selector*,struct xfrm_sec_ctx*,int,int*) ; 

__attribute__((used)) static int pfkey_spddelete(struct sock *sk, struct sk_buff *skb, const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	struct net *net = sock_net(sk);
	int err;
	struct sadb_address *sa;
	struct sadb_x_policy *pol;
	struct xfrm_policy *xp;
	struct xfrm_selector sel;
	struct km_event c;
	struct sadb_x_sec_ctx *sec_ctx;
	struct xfrm_sec_ctx *pol_ctx = NULL;

	if (!present_and_same_family(ext_hdrs[SADB_EXT_ADDRESS_SRC-1],
				     ext_hdrs[SADB_EXT_ADDRESS_DST-1]) ||
	    !ext_hdrs[SADB_X_EXT_POLICY-1])
		return -EINVAL;

	pol = ext_hdrs[SADB_X_EXT_POLICY-1];
	if (!pol->sadb_x_policy_dir || pol->sadb_x_policy_dir >= IPSEC_DIR_MAX)
		return -EINVAL;

	memset(&sel, 0, sizeof(sel));

	sa = ext_hdrs[SADB_EXT_ADDRESS_SRC-1];
	sel.family = pfkey_sadb_addr2xfrm_addr(sa, &sel.saddr);
	sel.prefixlen_s = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.sport = ((struct sockaddr_in *)(sa+1))->sin_port;
	if (sel.sport)
		sel.sport_mask = htons(0xffff);

	sa = ext_hdrs[SADB_EXT_ADDRESS_DST-1];
	pfkey_sadb_addr2xfrm_addr(sa, &sel.daddr);
	sel.prefixlen_d = sa->sadb_address_prefixlen;
	sel.proto = pfkey_proto_to_xfrm(sa->sadb_address_proto);
	sel.dport = ((struct sockaddr_in *)(sa+1))->sin_port;
	if (sel.dport)
		sel.dport_mask = htons(0xffff);

	sec_ctx = ext_hdrs[SADB_X_EXT_SEC_CTX - 1];
	if (sec_ctx != NULL) {
		struct xfrm_user_sec_ctx *uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx, GFP_KERNEL);

		if (!uctx)
			return -ENOMEM;

		err = security_xfrm_policy_alloc(&pol_ctx, uctx, GFP_KERNEL);
		kfree(uctx);
		if (err)
			return err;
	}

	xp = xfrm_policy_bysel_ctx(net, DUMMY_MARK, 0, XFRM_POLICY_TYPE_MAIN,
				   pol->sadb_x_policy_dir - 1, &sel, pol_ctx,
				   1, &err);
	security_xfrm_policy_free(pol_ctx);
	if (xp == NULL)
		return -ENOENT;

	xfrm_audit_policy_delete(xp, err ? 0 : 1, true);

	if (err)
		goto out;

	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	c.data.byid = 0;
	c.event = XFRM_MSG_DELPOLICY;
	km_policy_notify(xp, pol->sadb_x_policy_dir-1, &c);

out:
	xfrm_pol_put(xp);
	return err;
}