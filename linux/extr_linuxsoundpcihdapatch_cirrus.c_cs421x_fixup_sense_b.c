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
struct hda_codec {struct cs_spec* spec; } ;
struct cs_spec {int sense_b; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void cs421x_fixup_sense_b(struct hda_codec *codec,
				 const struct hda_fixup *fix, int action)
{
	struct cs_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->sense_b = 1;
}