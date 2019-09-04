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
struct bcm_op {scalar_t__ kt_ival2; int /*<<< orphan*/  timer; scalar_t__ kt_ival1; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void bcm_tx_start_timer(struct bcm_op *op)
{
	if (op->kt_ival1 && op->count)
		hrtimer_start(&op->timer,
			      ktime_add(ktime_get(), op->kt_ival1),
			      HRTIMER_MODE_ABS);
	else if (op->kt_ival2)
		hrtimer_start(&op->timer,
			      ktime_add(ktime_get(), op->kt_ival2),
			      HRTIMER_MODE_ABS);
}