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
struct bcm_op {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_SOFT ; 
 scalar_t__ bcm_tx_set_expiry (struct bcm_op*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_tx_start_timer(struct bcm_op *op)
{
	if (bcm_tx_set_expiry(op, &op->timer))
		hrtimer_start_expires(&op->timer, HRTIMER_MODE_ABS_SOFT);
}