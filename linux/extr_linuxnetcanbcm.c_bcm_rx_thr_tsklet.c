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
struct bcm_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_rx_thr_flush (struct bcm_op*,int) ; 

__attribute__((used)) static void bcm_rx_thr_tsklet(unsigned long data)
{
	struct bcm_op *op = (struct bcm_op *)data;

	/* push the changed data to the userspace */
	bcm_rx_thr_flush(op, 1);
}