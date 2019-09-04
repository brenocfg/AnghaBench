#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int event; } ;
struct TYPE_6__ {TYPE_1__ power_state; } ;
struct TYPE_7__ {TYPE_2__ power; } ;
struct rfkill {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  data; TYPE_4__* ops; TYPE_3__ dev; } ;
struct TYPE_8__ {int (* set_block ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* query ) (struct rfkill*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int PM_EVENT_SLEEP ; 
 int RFKILL_BLOCK_SW ; 
 int RFKILL_BLOCK_SW_PREV ; 
 int RFKILL_BLOCK_SW_SETCALL ; 
 int /*<<< orphan*/  rfkill_event (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_global_led_trigger_event () ; 
 int /*<<< orphan*/  rfkill_led_trigger_event (struct rfkill*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rfkill*,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rfkill_set_block(struct rfkill *rfkill, bool blocked)
{
	unsigned long flags;
	bool prev, curr;
	int err;

	if (unlikely(rfkill->dev.power.power_state.event & PM_EVENT_SLEEP))
		return;

	/*
	 * Some platforms (...!) generate input events which affect the
	 * _hard_ kill state -- whenever something tries to change the
	 * current software state query the hardware state too.
	 */
	if (rfkill->ops->query)
		rfkill->ops->query(rfkill, rfkill->data);

	spin_lock_irqsave(&rfkill->lock, flags);
	prev = rfkill->state & RFKILL_BLOCK_SW;

	if (prev)
		rfkill->state |= RFKILL_BLOCK_SW_PREV;
	else
		rfkill->state &= ~RFKILL_BLOCK_SW_PREV;

	if (blocked)
		rfkill->state |= RFKILL_BLOCK_SW;
	else
		rfkill->state &= ~RFKILL_BLOCK_SW;

	rfkill->state |= RFKILL_BLOCK_SW_SETCALL;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	err = rfkill->ops->set_block(rfkill->data, blocked);

	spin_lock_irqsave(&rfkill->lock, flags);
	if (err) {
		/*
		 * Failed -- reset status to _PREV, which may be different
		 * from what we have set _PREV to earlier in this function
		 * if rfkill_set_sw_state was invoked.
		 */
		if (rfkill->state & RFKILL_BLOCK_SW_PREV)
			rfkill->state |= RFKILL_BLOCK_SW;
		else
			rfkill->state &= ~RFKILL_BLOCK_SW;
	}
	rfkill->state &= ~RFKILL_BLOCK_SW_SETCALL;
	rfkill->state &= ~RFKILL_BLOCK_SW_PREV;
	curr = rfkill->state & RFKILL_BLOCK_SW;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	rfkill_led_trigger_event(rfkill);
	rfkill_global_led_trigger_event();

	if (prev != curr)
		rfkill_event(rfkill);
}