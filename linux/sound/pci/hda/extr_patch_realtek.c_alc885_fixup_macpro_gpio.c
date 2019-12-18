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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int gpio_write_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_fixup_gpio3 (struct hda_codec*,struct hda_fixup const*,int) ; 

__attribute__((used)) static void alc885_fixup_macpro_gpio(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	spec->gpio_write_delay = true;
	alc_fixup_gpio3(codec, fix, action);
}