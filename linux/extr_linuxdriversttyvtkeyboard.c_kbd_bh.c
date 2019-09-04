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
struct TYPE_2__ {scalar_t__ lockstate; } ;

/* Variables and functions */
 unsigned int getleds () ; 
 TYPE_1__* kbd ; 
 int /*<<< orphan*/  kbd_propagate_led_state (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  led_lock ; 
 unsigned int ledstate ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kbd_bh(unsigned long dummy)
{
	unsigned int leds;
	unsigned long flags;

	spin_lock_irqsave(&led_lock, flags);
	leds = getleds();
	leds |= (unsigned int)kbd->lockstate << 8;
	spin_unlock_irqrestore(&led_lock, flags);

	if (leds != ledstate) {
		kbd_propagate_led_state(ledstate, leds);
		ledstate = leds;
	}
}