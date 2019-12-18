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
struct snd_usb_audio {int /*<<< orphan*/  shutdown_wait; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int snd_usb_autoresume (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_usb_lock_shutdown(struct snd_usb_audio *chip)
{
	int err;

	atomic_inc(&chip->usage_count);
	if (atomic_read(&chip->shutdown)) {
		err = -EIO;
		goto error;
	}
	err = snd_usb_autoresume(chip);
	if (err < 0)
		goto error;
	return 0;

 error:
	if (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutdown_wait);
	return err;
}