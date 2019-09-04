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

/* Variables and functions */
 int /*<<< orphan*/  MISC_MAJOR ; 
 int /*<<< orphan*/  SYNTH_MINOR ; 
 scalar_t__ misc_register (int /*<<< orphan*/ *) ; 
 int misc_registered ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  synth_device ; 

void speakup_register_devsynth(void)
{
	if (misc_registered != 0)
		return;
/* zero it so if register fails, deregister will not ref invalid ptrs */
	if (misc_register(&synth_device)) {
		pr_warn("Couldn't initialize miscdevice /dev/synth.\n");
	} else {
		pr_info("initialized device: /dev/synth, node (MAJOR %d, MINOR %d)\n",
			MISC_MAJOR, SYNTH_MINOR);
		misc_registered = 1;
	}
}