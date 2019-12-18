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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_AMPCAP_MIN_MUTE ; 
 unsigned int AC_AMPCAP_MUTE ; 
 unsigned int AC_AMPCAP_NUM_STEPS ; 
 unsigned int AC_AMPCAP_OFFSET ; 
 unsigned int AC_AMPCAP_OFFSET_SHIFT ; 
 unsigned int HDA_AMP_MUTE ; 

__attribute__((used)) static int get_amp_val_to_activate(struct hda_codec *codec, hda_nid_t nid,
				   int dir, unsigned int caps, bool enable)
{
	unsigned int val = 0;

	if (caps & AC_AMPCAP_NUM_STEPS) {
		/* set to 0dB */
		if (enable)
			val = (caps & AC_AMPCAP_OFFSET) >> AC_AMPCAP_OFFSET_SHIFT;
	}
	if (caps & (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) {
		if (!enable)
			val |= HDA_AMP_MUTE;
	}
	return val;
}