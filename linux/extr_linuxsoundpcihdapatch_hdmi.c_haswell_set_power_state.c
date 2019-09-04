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
 unsigned int AC_PWRST_D0 ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  intel_haswell_enable_all_pins (struct hda_codec*,int) ; 
 int /*<<< orphan*/  intel_haswell_fixup_enable_dp12 (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_set_power_to_all (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void haswell_set_power_state(struct hda_codec *codec, hda_nid_t fg,
				unsigned int power_state)
{
	if (power_state == AC_PWRST_D0) {
		intel_haswell_enable_all_pins(codec, false);
		intel_haswell_fixup_enable_dp12(codec);
	}

	snd_hda_codec_read(codec, fg, 0, AC_VERB_SET_POWER_STATE, power_state);
	snd_hda_codec_set_power_to_all(codec, fg, power_state);
}