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
struct alc_spec {int /*<<< orphan*/  init_amp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_INIT_NONE ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void alc260_fixup_fsc_s7020(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->init_amp = ALC_INIT_NONE;
}