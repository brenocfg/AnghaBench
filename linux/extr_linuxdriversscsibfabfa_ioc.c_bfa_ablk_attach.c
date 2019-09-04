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
struct bfa_ioc_s {int /*<<< orphan*/  notify_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  qe; } ;
struct bfa_ablk_s {struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_ABLK ; 
 int /*<<< orphan*/  bfa_ablk_isr ; 
 int /*<<< orphan*/  bfa_ablk_notify ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_ablk_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_ablk_s*) ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_ablk_attach(struct bfa_ablk_s *ablk, struct bfa_ioc_s *ioc)
{
	ablk->ioc = ioc;

	bfa_ioc_mbox_regisr(ablk->ioc, BFI_MC_ABLK, bfa_ablk_isr, ablk);
	bfa_q_qe_init(&ablk->ioc_notify);
	bfa_ioc_notify_init(&ablk->ioc_notify, bfa_ablk_notify, ablk);
	list_add_tail(&ablk->ioc_notify.qe, &ablk->ioc->notify_q);
}