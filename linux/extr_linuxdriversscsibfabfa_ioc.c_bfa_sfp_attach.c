#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_trc_mod_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qe; } ;
struct bfa_sfp_s {struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; int /*<<< orphan*/  is_elb; int /*<<< orphan*/  portspeed; int /*<<< orphan*/ * media; int /*<<< orphan*/ * state_query_cbarg; int /*<<< orphan*/ * state_query_cbfn; scalar_t__ state_query_lock; int /*<<< orphan*/  state; scalar_t__ data_valid; scalar_t__ lock; int /*<<< orphan*/ * sfpmem; int /*<<< orphan*/ * cbarg; int /*<<< orphan*/ * cbfn; struct bfa_trc_mod_s* trcmod; void* dev; } ;
struct bfa_ioc_s {int /*<<< orphan*/  notify_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  BFA_SFP_STATE_INIT ; 
 int /*<<< orphan*/  BFI_MC_SFP ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_sfp_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_sfp_s*) ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_sfp_intr ; 
 int /*<<< orphan*/  bfa_sfp_notify ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_sfp_attach(struct bfa_sfp_s *sfp, struct bfa_ioc_s *ioc, void *dev,
		struct bfa_trc_mod_s *trcmod)
{
	sfp->dev = dev;
	sfp->ioc = ioc;
	sfp->trcmod = trcmod;

	sfp->cbfn = NULL;
	sfp->cbarg = NULL;
	sfp->sfpmem = NULL;
	sfp->lock = 0;
	sfp->data_valid = 0;
	sfp->state = BFA_SFP_STATE_INIT;
	sfp->state_query_lock = 0;
	sfp->state_query_cbfn = NULL;
	sfp->state_query_cbarg = NULL;
	sfp->media = NULL;
	sfp->portspeed = BFA_PORT_SPEED_UNKNOWN;
	sfp->is_elb = BFA_FALSE;

	bfa_ioc_mbox_regisr(sfp->ioc, BFI_MC_SFP, bfa_sfp_intr, sfp);
	bfa_q_qe_init(&sfp->ioc_notify);
	bfa_ioc_notify_init(&sfp->ioc_notify, bfa_sfp_notify, sfp);
	list_add_tail(&sfp->ioc_notify.qe, &sfp->ioc->notify_q);
}