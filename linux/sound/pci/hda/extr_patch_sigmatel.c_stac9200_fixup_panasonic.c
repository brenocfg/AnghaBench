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
struct TYPE_2__ {int suppress_auto_mute; } ;
struct sigmatel_spec {int gpio_mask; int gpio_dir; int gpio_data; TYPE_1__ gen; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void stac9200_fixup_panasonic(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gpio_mask = spec->gpio_dir = 0x09;
		spec->gpio_data = 0x00;
		/* CF-74 has no headphone detection, and the driver should *NOT*
		 * do detection and HP/speaker toggle because the hardware does it.
		 */
		spec->gen.suppress_auto_mute = 1;
	}
}