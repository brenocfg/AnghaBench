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
struct TYPE_2__ {int can_queue; int /*<<< orphan*/  pend_q_lock; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;

/* Variables and functions */
 int SAS_QUEUE_FULL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int asd_can_queue(struct asd_ha_struct *asd_ha, int num)
{
	int res = 0;
	unsigned long flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	if ((asd_ha->seq.can_queue - num) < 0)
		res = -SAS_QUEUE_FULL;
	else
		asd_ha->seq.can_queue -= num;
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	return res;
}