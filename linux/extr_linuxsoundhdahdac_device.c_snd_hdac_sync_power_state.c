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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_ERROR ; 
 int /*<<< orphan*/  AC_VERB_GET_POWER_STATE ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int snd_hdac_codec_read (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

unsigned int snd_hdac_sync_power_state(struct hdac_device *codec,
			hda_nid_t nid, unsigned int power_state)
{
	unsigned long end_time = jiffies + msecs_to_jiffies(500);
	unsigned int state, actual_state, count;

	for (count = 0; count < 500; count++) {
		state = snd_hdac_codec_read(codec, nid, 0,
				AC_VERB_GET_POWER_STATE, 0);
		if (state & AC_PWRST_ERROR) {
			msleep(20);
			break;
		}
		actual_state = (state >> 4) & 0x0f;
		if (actual_state == power_state)
			break;
		if (time_after_eq(jiffies, end_time))
			break;
		/* wait until the codec reachs to the target state */
		msleep(1);
	}
	return state;
}