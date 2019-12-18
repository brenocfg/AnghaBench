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
typedef  int /*<<< orphan*/  u64 ;
struct sugov_policy {int work_in_progress; int /*<<< orphan*/  irq_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sugov_update_next_freq (struct sugov_policy*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sugov_deferred_update(struct sugov_policy *sg_policy, u64 time,
				  unsigned int next_freq)
{
	if (!sugov_update_next_freq(sg_policy, time, next_freq))
		return;

	if (!sg_policy->work_in_progress) {
		sg_policy->work_in_progress = true;
		irq_work_queue(&sg_policy->irq_work);
	}
}