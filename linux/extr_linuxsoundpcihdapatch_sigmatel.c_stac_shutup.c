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
struct sigmatel_spec {int eapd_mask; int gpio_data; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_shutup_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  stac_gpio_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stac_shutup(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;

	snd_hda_shutup_pins(codec);

	if (spec->eapd_mask)
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_dir, spec->gpio_data &
				~spec->eapd_mask);
}