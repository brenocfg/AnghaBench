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
struct bcm_op {int flags; scalar_t__ kt_ival1; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_SOFT ; 
 int RX_NO_AUTOTIMER ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_rx_starttimer(struct bcm_op *op)
{
	if (op->flags & RX_NO_AUTOTIMER)
		return;

	if (op->kt_ival1)
		hrtimer_start(&op->timer, op->kt_ival1, HRTIMER_MODE_REL_SOFT);
}