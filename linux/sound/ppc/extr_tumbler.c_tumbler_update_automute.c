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
struct snd_pmac {struct pmac_tumbler* mixer_data; scalar_t__ auto_mute; } ;
struct pmac_tumbler {int auto_mute_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_change ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static void tumbler_update_automute(struct snd_pmac *chip, int do_notify)
{
	if (chip->auto_mute) {
		struct pmac_tumbler *mix;
		mix = chip->mixer_data;
		if (snd_BUG_ON(!mix))
			return;
		mix->auto_mute_notify = do_notify;
		schedule_work(&device_change);
	}
}