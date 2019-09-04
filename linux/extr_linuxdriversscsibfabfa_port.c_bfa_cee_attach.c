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
struct bfa_cee_s {struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; void* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_CEE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_cee_isr ; 
 int /*<<< orphan*/  bfa_cee_notify ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_cee_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_cee_s*) ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_cee_attach(struct bfa_cee_s *cee, struct bfa_ioc_s *ioc,
		void *dev)
{
	WARN_ON(cee == NULL);
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_ioc_mbox_regisr(cee->ioc, BFI_MC_CEE, bfa_cee_isr, cee);
	bfa_q_qe_init(&cee->ioc_notify);
	bfa_ioc_notify_init(&cee->ioc_notify, bfa_cee_notify, cee);
	list_add_tail(&cee->ioc_notify.qe, &cee->ioc->notify_q);
}