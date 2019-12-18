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
struct bcm_op {int nframes; } ;

/* Variables and functions */
 scalar_t__ bcm_rx_do_flush (struct bcm_op*,unsigned int) ; 

__attribute__((used)) static int bcm_rx_thr_flush(struct bcm_op *op)
{
	int updated = 0;

	if (op->nframes > 1) {
		unsigned int i;

		/* for MUX filter we start at index 1 */
		for (i = 1; i < op->nframes; i++)
			updated += bcm_rx_do_flush(op, i);

	} else {
		/* for RX_FILTER_ID and simple filter */
		updated += bcm_rx_do_flush(op, 0);
	}

	return updated;
}