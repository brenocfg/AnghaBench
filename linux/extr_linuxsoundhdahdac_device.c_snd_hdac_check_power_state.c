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
 unsigned int codec_read (struct hdac_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool snd_hdac_check_power_state(struct hdac_device *hdac,
		hda_nid_t nid, unsigned int target_state)
{
	unsigned int state = codec_read(hdac, nid, 0,
				AC_VERB_GET_POWER_STATE, 0);

	if (state & AC_PWRST_ERROR)
		return true;
	state = (state >> 4) & 0x0f;
	return (state == target_state);
}