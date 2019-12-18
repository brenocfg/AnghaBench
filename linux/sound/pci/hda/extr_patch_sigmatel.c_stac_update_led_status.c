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
struct sigmatel_spec {int /*<<< orphan*/  vref_led; int /*<<< orphan*/  vref_mute_led_nid; int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  gpio_led; scalar_t__ gpio_led_polarity; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PINCTL_VREF_50 ; 
 int /*<<< orphan*/  AC_PINCTL_VREF_GRD ; 
 int /*<<< orphan*/  stac_gpio_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac_vrefout_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac_update_led_status(struct hda_codec *codec, int enabled)
{
	struct sigmatel_spec *spec = codec->spec;
	int muted = !enabled;

	if (!spec->gpio_led)
		return;

	/* LED state is inverted on these systems */
	if (spec->gpio_led_polarity)
		muted = !muted;

	if (!spec->vref_mute_led_nid) {
		if (muted)
			spec->gpio_data |= spec->gpio_led;
		else
			spec->gpio_data &= ~spec->gpio_led;
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_dir, spec->gpio_data);
	} else {
		spec->vref_led = muted ? AC_PINCTL_VREF_50 : AC_PINCTL_VREF_GRD;
		stac_vrefout_set(codec,	spec->vref_mute_led_nid,
				 spec->vref_led);
	}
}