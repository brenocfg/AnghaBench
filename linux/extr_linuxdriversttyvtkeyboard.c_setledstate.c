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
struct kbd_struct {int /*<<< orphan*/  ledmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_SHOW_FLAGS ; 
 int /*<<< orphan*/  LED_SHOW_IOCTL ; 
 int /*<<< orphan*/  led_lock ; 
 unsigned int ledioctl ; 
 int /*<<< orphan*/  set_leds () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void setledstate(struct kbd_struct *kb, unsigned int led)
{
        unsigned long flags;
        spin_lock_irqsave(&led_lock, flags);
	if (!(led & ~7)) {
		ledioctl = led;
		kb->ledmode = LED_SHOW_IOCTL;
	} else
		kb->ledmode = LED_SHOW_FLAGS;

	set_leds();
	spin_unlock_irqrestore(&led_lock, flags);
}