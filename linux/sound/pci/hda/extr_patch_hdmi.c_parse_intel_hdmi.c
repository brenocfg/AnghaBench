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

/* Variables and functions */
 int /*<<< orphan*/  generic_hdmi_init_per_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  generic_spec_free (struct hda_codec*) ; 
 int hdmi_parse_codec (struct hda_codec*) ; 
 int /*<<< orphan*/  register_i915_notifier (struct hda_codec*) ; 

__attribute__((used)) static int parse_intel_hdmi(struct hda_codec *codec)
{
	int err;

	err = hdmi_parse_codec(codec);
	if (err < 0) {
		generic_spec_free(codec);
		return err;
	}

	generic_hdmi_init_per_pins(codec);
	register_i915_notifier(codec);
	return 0;
}