#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int has_fx; int /*<<< orphan*/  control_port; scalar_t__ israw; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 scalar_t__ fx_raw ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_wavefront_fx_detect (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_wavefront_fx_start (TYPE_1__*) ; 
 scalar_t__ wavefront_do_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  wavefront_get_patch_status (TYPE_1__*) ; 
 int /*<<< orphan*/  wavefront_get_program_status (TYPE_1__*) ; 
 int /*<<< orphan*/  wavefront_get_sample_status (TYPE_1__*,int) ; 

int
snd_wavefront_start (snd_wavefront_t *dev)

{
	int samples_are_from_rom;

	/* IMPORTANT: assumes that snd_wavefront_detect() and/or
	   wavefront_reset_to_cleanliness() has already been called 
	*/

	if (dev->israw) {
		samples_are_from_rom = 1;
	} else {
		/* XXX is this always true ? */
		samples_are_from_rom = 0;
	}

	if (dev->israw || fx_raw) {
		if (wavefront_do_reset (dev)) {
			return -1;
		}
	}
	/* Check for FX device, present only on Tropez+ */

	dev->has_fx = (snd_wavefront_fx_detect (dev) == 0);

	if (dev->has_fx && fx_raw) {
		snd_wavefront_fx_start (dev);
	}

	wavefront_get_sample_status (dev, samples_are_from_rom);
	wavefront_get_program_status (dev);
	wavefront_get_patch_status (dev);

	/* Start normal operation: unreset, master interrupt enabled, no mute
	*/

	outb (0x80|0x40|0x20, dev->control_port); 

	return (0);
}