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
struct sfire_chip {struct midi_runtime* midi; } ;
struct midi_runtime {int /*<<< orphan*/  out_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ *) ; 

void usb6fire_midi_abort(struct sfire_chip *chip)
{
	struct midi_runtime *rt = chip->midi;

	if (rt)
		usb_poison_urb(&rt->out_urb);
}