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
struct midi_runtime {struct midi_runtime* out_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct midi_runtime*) ; 

void usb6fire_midi_destroy(struct sfire_chip *chip)
{
	struct midi_runtime *rt = chip->midi;

	kfree(rt->out_buffer);
	kfree(rt);
	chip->midi = NULL;
}