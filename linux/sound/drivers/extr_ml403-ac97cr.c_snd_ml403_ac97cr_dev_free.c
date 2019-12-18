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
struct snd_ml403_ac97cr {int dummy; } ;
struct snd_device {struct snd_ml403_ac97cr* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_INFO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int snd_ml403_ac97cr_free (struct snd_ml403_ac97cr*) ; 

__attribute__((used)) static int snd_ml403_ac97cr_dev_free(struct snd_device *snddev)
{
	struct snd_ml403_ac97cr *ml403_ac97cr = snddev->device_data;
	PDEBUG(INIT_INFO, "dev_free():\n");
	return snd_ml403_ac97cr_free(ml403_ac97cr);
}