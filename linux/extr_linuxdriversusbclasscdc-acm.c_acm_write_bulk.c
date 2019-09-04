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
struct urb {int status; scalar_t__ actual_length; scalar_t__ transfer_buffer_length; struct acm_wb* context; } ;
struct acm_wb {struct acm* instance; } ;
struct acm {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; int /*<<< orphan*/  write_lock; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TTY_WAKEUP ; 
 int /*<<< orphan*/  acm_write_done (struct acm*,struct acm_wb*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void acm_write_bulk(struct urb *urb)
{
	struct acm_wb *wb = urb->context;
	struct acm *acm = wb->instance;
	unsigned long flags;
	int status = urb->status;

	if (status || (urb->actual_length != urb->transfer_buffer_length))
		dev_vdbg(&acm->data->dev, "wrote len %d/%d, status %d\n",
			urb->actual_length,
			urb->transfer_buffer_length,
			status);

	spin_lock_irqsave(&acm->write_lock, flags);
	acm_write_done(acm, wb);
	spin_unlock_irqrestore(&acm->write_lock, flags);
	set_bit(EVENT_TTY_WAKEUP, &acm->flags);
	schedule_work(&acm->work);
}