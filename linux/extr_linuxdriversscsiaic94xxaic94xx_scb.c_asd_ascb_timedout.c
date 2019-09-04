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
struct timer_list {int dummy; } ;
struct asd_seq_data {int /*<<< orphan*/  pend_q_lock; int /*<<< orphan*/  pending; } ;
struct asd_ascb {int /*<<< orphan*/  list; TYPE_3__* scb; TYPE_1__* ha; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {TYPE_2__ header; } ;
struct TYPE_4__ {struct asd_seq_data seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int /*<<< orphan*/ ) ; 
 struct asd_ascb* ascb ; 
 int /*<<< orphan*/  asd_ascb_free (struct asd_ascb*) ; 
 struct asd_ascb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

void asd_ascb_timedout(struct timer_list *t)
{
	struct asd_ascb *ascb = from_timer(ascb, t, timer);
	struct asd_seq_data *seq = &ascb->ha->seq;
	unsigned long flags;

	ASD_DPRINTK("scb:0x%x timed out\n", ascb->scb->header.opcode);

	spin_lock_irqsave(&seq->pend_q_lock, flags);
	seq->pending--;
	list_del_init(&ascb->list);
	spin_unlock_irqrestore(&seq->pend_q_lock, flags);

	asd_ascb_free(ascb);
}