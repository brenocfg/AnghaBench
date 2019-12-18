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
struct canfd_frame {int flags; } ;
struct bcm_op {unsigned int cfsiz; struct canfd_frame* last_frames; } ;

/* Variables and functions */
 int RX_THR ; 
 int /*<<< orphan*/  bcm_rx_changed (struct bcm_op*,struct canfd_frame*) ; 

__attribute__((used)) static inline int bcm_rx_do_flush(struct bcm_op *op, unsigned int index)
{
	struct canfd_frame *lcf = op->last_frames + op->cfsiz * index;

	if ((op->last_frames) && (lcf->flags & RX_THR)) {
		bcm_rx_changed(op, lcf);
		return 1;
	}
	return 0;
}