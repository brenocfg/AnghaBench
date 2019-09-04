#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  prev; } ;
struct TYPE_7__ {int pending; int /*<<< orphan*/  pend_q_lock; scalar_t__ scbpro; TYPE_2__ pend_q; } ;
struct TYPE_5__ {int max_scbs; } ;
struct asd_ha_struct {TYPE_3__ seq; int /*<<< orphan*/  pcidev; TYPE_1__ hw_prof; } ;
struct TYPE_8__ {int /*<<< orphan*/  prev; } ;
struct asd_ascb {TYPE_4__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int SAS_QUEUE_FULL ; 
 int /*<<< orphan*/  SCBPRO ; 
 int /*<<< orphan*/  __list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_start_scb_timers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asd_swap_head_scb (struct asd_ha_struct*,struct asd_ascb*) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int asd_post_ascb_list(struct asd_ha_struct *asd_ha, struct asd_ascb *ascb,
		       int num)
{
	unsigned long flags;
	LIST_HEAD(list);
	int can_queue;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	can_queue = asd_ha->hw_prof.max_scbs - asd_ha->seq.pending;
	if (can_queue >= num)
		asd_ha->seq.pending += num;
	else
		can_queue = 0;

	if (!can_queue) {
		spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);
		asd_printk("%s: scb queue full\n", pci_name(asd_ha->pcidev));
		return -SAS_QUEUE_FULL;
	}

	asd_swap_head_scb(asd_ha, ascb);

	__list_add(&list, ascb->list.prev, &ascb->list);

	asd_start_scb_timers(&list);

	asd_ha->seq.scbpro += num;
	list_splice_init(&list, asd_ha->seq.pend_q.prev);
	asd_write_reg_dword(asd_ha, SCBPRO, (u32)asd_ha->seq.scbpro);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	return 0;
}