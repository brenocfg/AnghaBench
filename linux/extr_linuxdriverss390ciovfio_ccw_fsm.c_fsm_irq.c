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
struct vfio_ccw_private {scalar_t__ completion; int /*<<< orphan*/  io_work; int /*<<< orphan*/  irb; } ;
struct irb {int dummy; } ;
typedef  enum vfio_ccw_event { ____Placeholder_vfio_ccw_event } vfio_ccw_event ;

/* Variables and functions */
 int /*<<< orphan*/  cio_irb ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct irb*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct irb* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ccw_work_q ; 

__attribute__((used)) static void fsm_irq(struct vfio_ccw_private *private,
		    enum vfio_ccw_event event)
{
	struct irb *irb = this_cpu_ptr(&cio_irb);

	memcpy(&private->irb, irb, sizeof(*irb));

	queue_work(vfio_ccw_work_q, &private->io_work);

	if (private->completion)
		complete(private->completion);
}