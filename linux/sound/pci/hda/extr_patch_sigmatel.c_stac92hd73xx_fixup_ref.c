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
struct sigmatel_spec {scalar_t__ gpio_data; scalar_t__ gpio_dir; scalar_t__ gpio_mask; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  ref92hd73xx_pin_configs ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac92hd73xx_fixup_ref(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	snd_hda_apply_pincfgs(codec, ref92hd73xx_pin_configs);
	spec->gpio_mask = spec->gpio_dir = spec->gpio_data = 0;
}