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
struct snd_usb_audio {int /*<<< orphan*/  shutdown_wait; int /*<<< orphan*/  usage_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usb_autosuspend (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_usb_unlock_shutdown(struct snd_usb_audio *chip)
{
	snd_usb_autosuspend(chip);
	if (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutdown_wait);
}