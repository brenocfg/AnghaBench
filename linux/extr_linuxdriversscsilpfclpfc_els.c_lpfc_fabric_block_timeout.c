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
typedef  int uint32_t ;
struct timer_list {int dummy; } ;
struct lpfc_hba {TYPE_1__* pport; } ;
struct TYPE_2__ {int work_port_events; int /*<<< orphan*/  work_port_lock; } ;

/* Variables and functions */
 int WORKER_FABRIC_BLOCK_TMO ; 
 int /*<<< orphan*/  fabric_block_timer ; 
 struct lpfc_hba* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 struct lpfc_hba* phba ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
lpfc_fabric_block_timeout(struct timer_list *t)
{
	struct lpfc_hba  *phba = from_timer(phba, t, fabric_block_timer);
	unsigned long iflags;
	uint32_t tmo_posted;

	spin_lock_irqsave(&phba->pport->work_port_lock, iflags);
	tmo_posted = phba->pport->work_port_events & WORKER_FABRIC_BLOCK_TMO;
	if (!tmo_posted)
		phba->pport->work_port_events |= WORKER_FABRIC_BLOCK_TMO;
	spin_unlock_irqrestore(&phba->pport->work_port_lock, iflags);

	if (!tmo_posted)
		lpfc_worker_wake_up(phba);
	return;
}