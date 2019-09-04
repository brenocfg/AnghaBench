#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mixer_build {int /*<<< orphan*/  chip; int /*<<< orphan*/  unitbitmap; TYPE_1__* mixer; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int EINVAL ; 
#define  UAC1_EXTENSION_UNIT 144 
#define  UAC1_PROCESSING_UNIT 143 
#define  UAC2_CLOCK_SELECTOR 142 
#define  UAC2_CLOCK_SOURCE 141 
#define  UAC2_EXTENSION_UNIT_V2 140 
#define  UAC3_CLOCK_SELECTOR 139 
#define  UAC3_CLOCK_SOURCE 138 
#define  UAC3_EFFECT_UNIT 137 
#define  UAC3_EXTENSION_UNIT 136 
#define  UAC3_FEATURE_UNIT 135 
#define  UAC3_MIXER_UNIT 134 
#define  UAC3_PROCESSING_UNIT 133 
#define  UAC3_SELECTOR_UNIT 132 
#define  UAC_FEATURE_UNIT 131 
#define  UAC_INPUT_TERMINAL 130 
#define  UAC_MIXER_UNIT 129 
#define  UAC_SELECTOR_UNIT 128 
 int UAC_VERSION_1 ; 
 int UAC_VERSION_2 ; 
 unsigned char* find_audio_control_unit (struct mixer_build*,int) ; 
 int parse_audio_extension_unit (struct mixer_build*,int,unsigned char*) ; 
 int parse_audio_feature_unit (struct mixer_build*,int,unsigned char*) ; 
 int parse_audio_input_terminal (struct mixer_build*,int,unsigned char*) ; 
 int parse_audio_mixer_unit (struct mixer_build*,int,unsigned char*) ; 
 int parse_audio_processing_unit (struct mixer_build*,int,unsigned char*) ; 
 int parse_audio_selector_unit (struct mixer_build*,int,unsigned char*) ; 
 int parse_clock_source_unit (struct mixer_build*,int,unsigned char*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int parse_audio_unit(struct mixer_build *state, int unitid)
{
	unsigned char *p1;
	int protocol = state->mixer->protocol;

	if (test_and_set_bit(unitid, state->unitbitmap))
		return 0; /* the unit already visited */

	p1 = find_audio_control_unit(state, unitid);
	if (!p1) {
		usb_audio_err(state->chip, "unit %d not found!\n", unitid);
		return -EINVAL;
	}

	if (protocol == UAC_VERSION_1 || protocol == UAC_VERSION_2) {
		switch (p1[2]) {
		case UAC_INPUT_TERMINAL:
			return parse_audio_input_terminal(state, unitid, p1);
		case UAC_MIXER_UNIT:
			return parse_audio_mixer_unit(state, unitid, p1);
		case UAC2_CLOCK_SOURCE:
			return parse_clock_source_unit(state, unitid, p1);
		case UAC_SELECTOR_UNIT:
		case UAC2_CLOCK_SELECTOR:
			return parse_audio_selector_unit(state, unitid, p1);
		case UAC_FEATURE_UNIT:
			return parse_audio_feature_unit(state, unitid, p1);
		case UAC1_PROCESSING_UNIT:
		/*   UAC2_EFFECT_UNIT has the same value */
			if (protocol == UAC_VERSION_1)
				return parse_audio_processing_unit(state, unitid, p1);
			else
				return 0; /* FIXME - effect units not implemented yet */
		case UAC1_EXTENSION_UNIT:
		/*   UAC2_PROCESSING_UNIT_V2 has the same value */
			if (protocol == UAC_VERSION_1)
				return parse_audio_extension_unit(state, unitid, p1);
			else /* UAC_VERSION_2 */
				return parse_audio_processing_unit(state, unitid, p1);
		case UAC2_EXTENSION_UNIT_V2:
			return parse_audio_extension_unit(state, unitid, p1);
		default:
			usb_audio_err(state->chip,
				"unit %u: unexpected type 0x%02x\n", unitid, p1[2]);
			return -EINVAL;
		}
	} else { /* UAC_VERSION_3 */
		switch (p1[2]) {
		case UAC_INPUT_TERMINAL:
			return parse_audio_input_terminal(state, unitid, p1);
		case UAC3_MIXER_UNIT:
			return parse_audio_mixer_unit(state, unitid, p1);
		case UAC3_CLOCK_SOURCE:
			return parse_clock_source_unit(state, unitid, p1);
		case UAC3_SELECTOR_UNIT:
		case UAC3_CLOCK_SELECTOR:
			return parse_audio_selector_unit(state, unitid, p1);
		case UAC3_FEATURE_UNIT:
			return parse_audio_feature_unit(state, unitid, p1);
		case UAC3_EFFECT_UNIT:
			return 0; /* FIXME - effect units not implemented yet */
		case UAC3_PROCESSING_UNIT:
			return parse_audio_processing_unit(state, unitid, p1);
		case UAC3_EXTENSION_UNIT:
			return parse_audio_extension_unit(state, unitid, p1);
		default:
			usb_audio_err(state->chip,
				"unit %u: unexpected type 0x%02x\n", unitid, p1[2]);
			return -EINVAL;
		}
	}
}