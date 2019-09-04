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
struct comedi_subdevice {int /*<<< orphan*/  spin_lock; struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  async_queue; } ;
struct TYPE_2__ {int flags; } ;
struct comedi_async {unsigned int events; unsigned int cb_mask; TYPE_1__ cmd; int /*<<< orphan*/  wait_head; } ;

/* Variables and functions */
 int CMDF_WRITE ; 
 unsigned int COMEDI_CB_CANCEL_MASK ; 
 unsigned int COMEDI_CB_ERROR_MASK ; 
 int /*<<< orphan*/  COMEDI_SRF_ERROR ; 
 int /*<<< orphan*/  COMEDI_SRF_RUNNING ; 
 int POLL_IN ; 
 int POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  __comedi_clear_subdevice_runflags (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __comedi_is_subdevice_running (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  __comedi_set_subdevice_runflags (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void comedi_event(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	unsigned int events;
	int si_code = 0;
	unsigned long flags;

	spin_lock_irqsave(&s->spin_lock, flags);

	events = async->events;
	async->events = 0;
	if (!__comedi_is_subdevice_running(s)) {
		spin_unlock_irqrestore(&s->spin_lock, flags);
		return;
	}

	if (events & COMEDI_CB_CANCEL_MASK)
		__comedi_clear_subdevice_runflags(s, COMEDI_SRF_RUNNING);

	/*
	 * Remember if an error event has occurred, so an error can be
	 * returned the next time the user does a read() or write().
	 */
	if (events & COMEDI_CB_ERROR_MASK)
		__comedi_set_subdevice_runflags(s, COMEDI_SRF_ERROR);

	if (async->cb_mask & events) {
		wake_up_interruptible(&async->wait_head);
		si_code = async->cmd.flags & CMDF_WRITE ? POLL_OUT : POLL_IN;
	}

	spin_unlock_irqrestore(&s->spin_lock, flags);

	if (si_code)
		kill_fasync(&dev->async_queue, SIGIO, si_code);
}