#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfrm_usersa_info {int /*<<< orphan*/  seq; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  smark; int /*<<< orphan*/  calgo; int /*<<< orphan*/  aalgo; void* extra_flags; } ;
struct xfrm_state {int replay_maxage; TYPE_3__ km; int /*<<< orphan*/  replay_maxdiff; int /*<<< orphan*/  preplay_esn; int /*<<< orphan*/  replay_esn; void* if_id; TYPE_1__ props; int /*<<< orphan*/  mark; int /*<<< orphan*/ * coaddr; void* tfcpad; int /*<<< orphan*/ * encap; int /*<<< orphan*/  calg; int /*<<< orphan*/  aalg; } ;
struct nlattr {int dummy; } ;
struct TYPE_5__ {int sysctl_aevent_etime; int /*<<< orphan*/  sysctl_aevent_rseqth; } ;
struct net {TYPE_2__ xfrm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 size_t XFRMA_ALG_AEAD ; 
 size_t XFRMA_ALG_AUTH ; 
 size_t XFRMA_ALG_AUTH_TRUNC ; 
 size_t XFRMA_ALG_COMP ; 
 size_t XFRMA_ALG_CRYPT ; 
 size_t XFRMA_COADDR ; 
 size_t XFRMA_ENCAP ; 
 size_t XFRMA_IF_ID ; 
 size_t XFRMA_OFFLOAD_DEV ; 
 size_t XFRMA_REPLAY_ESN_VAL ; 
 size_t XFRMA_SA_EXTRA_FLAGS ; 
 size_t XFRMA_SEC_CTX ; 
 size_t XFRMA_TFCPAD ; 
 int XFRM_AE_ETH_M ; 
 int /*<<< orphan*/  XFRM_STATE_DEAD ; 
 int __xfrm_init_state (struct xfrm_state*,int,struct nlattr*) ; 
 int attach_aead (struct xfrm_state*,struct nlattr*) ; 
 int attach_auth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int attach_auth_trunc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int attach_crypt (struct xfrm_state*,struct nlattr*) ; 
 int attach_one_algo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  copy_from_user_state (struct xfrm_state*,struct xfrm_usersa_info*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int security_xfrm_state_alloc (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int xfrm_alloc_replay_state_esn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int /*<<< orphan*/  xfrm_calg_get_byname ; 
 int xfrm_dev_state_add (struct net*,struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int xfrm_init_replay (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_smark_init (struct nlattr**,int /*<<< orphan*/ *) ; 
 struct xfrm_state* xfrm_state_alloc (struct net*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_update_ae_params (struct xfrm_state*,struct nlattr**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_state *xfrm_state_construct(struct net *net,
					       struct xfrm_usersa_info *p,
					       struct nlattr **attrs,
					       int *errp)
{
	struct xfrm_state *x = xfrm_state_alloc(net);
	int err = -ENOMEM;

	if (!x)
		goto error_no_put;

	copy_from_user_state(x, p);

	if (attrs[XFRMA_SA_EXTRA_FLAGS])
		x->props.extra_flags = nla_get_u32(attrs[XFRMA_SA_EXTRA_FLAGS]);

	if ((err = attach_aead(x, attrs[XFRMA_ALG_AEAD])))
		goto error;
	if ((err = attach_auth_trunc(&x->aalg, &x->props.aalgo,
				     attrs[XFRMA_ALG_AUTH_TRUNC])))
		goto error;
	if (!x->props.aalgo) {
		if ((err = attach_auth(&x->aalg, &x->props.aalgo,
				       attrs[XFRMA_ALG_AUTH])))
			goto error;
	}
	if ((err = attach_crypt(x, attrs[XFRMA_ALG_CRYPT])))
		goto error;
	if ((err = attach_one_algo(&x->calg, &x->props.calgo,
				   xfrm_calg_get_byname,
				   attrs[XFRMA_ALG_COMP])))
		goto error;

	if (attrs[XFRMA_ENCAP]) {
		x->encap = kmemdup(nla_data(attrs[XFRMA_ENCAP]),
				   sizeof(*x->encap), GFP_KERNEL);
		if (x->encap == NULL)
			goto error;
	}

	if (attrs[XFRMA_TFCPAD])
		x->tfcpad = nla_get_u32(attrs[XFRMA_TFCPAD]);

	if (attrs[XFRMA_COADDR]) {
		x->coaddr = kmemdup(nla_data(attrs[XFRMA_COADDR]),
				    sizeof(*x->coaddr), GFP_KERNEL);
		if (x->coaddr == NULL)
			goto error;
	}

	xfrm_mark_get(attrs, &x->mark);

	xfrm_smark_init(attrs, &x->props.smark);

	if (attrs[XFRMA_IF_ID])
		x->if_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	err = __xfrm_init_state(x, false, attrs[XFRMA_OFFLOAD_DEV]);
	if (err)
		goto error;

	if (attrs[XFRMA_SEC_CTX]) {
		err = security_xfrm_state_alloc(x,
						nla_data(attrs[XFRMA_SEC_CTX]));
		if (err)
			goto error;
	}

	if ((err = xfrm_alloc_replay_state_esn(&x->replay_esn, &x->preplay_esn,
					       attrs[XFRMA_REPLAY_ESN_VAL])))
		goto error;

	x->km.seq = p->seq;
	x->replay_maxdiff = net->xfrm.sysctl_aevent_rseqth;
	/* sysctl_xfrm_aevent_etime is in 100ms units */
	x->replay_maxage = (net->xfrm.sysctl_aevent_etime*HZ)/XFRM_AE_ETH_M;

	if ((err = xfrm_init_replay(x)))
		goto error;

	/* override default values from above */
	xfrm_update_ae_params(x, attrs, 0);

	/* configure the hardware if offload is requested */
	if (attrs[XFRMA_OFFLOAD_DEV]) {
		err = xfrm_dev_state_add(net, x,
					 nla_data(attrs[XFRMA_OFFLOAD_DEV]));
		if (err)
			goto error;
	}

	return x;

error:
	x->km.state = XFRM_STATE_DEAD;
	xfrm_state_put(x);
error_no_put:
	*errp = err;
	return NULL;
}