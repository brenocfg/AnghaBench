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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_INIT ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alc269_fixup_stereo_dmic(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	/* The digital-mic unit sends PDM (differential signal) instead of
	 * the standard PCM, thus you can't record a valid mono stream as is.
	 * Below is a workaround specific to ALC269 to control the dmic
	 * signal source as mono.
	 */
	if (action == HDA_FIXUP_ACT_INIT)
		alc_update_coef_idx(codec, 0x07, 0, 0x80);
}