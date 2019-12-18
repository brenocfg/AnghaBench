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
 unsigned int AC_UNSOL_RES_SUBTAG ; 
 unsigned int AC_UNSOL_RES_SUBTAG_SHIFT ; 
 unsigned int AC_UNSOL_RES_TAG_SHIFT ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int) ; 
 scalar_t__ codec_has_acomp (struct hda_codec*) ; 
 int /*<<< orphan*/  hdmi_intrinsic_event (struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  hdmi_non_intrinsic_event (struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_jack_tbl_get_from_tag (struct hda_codec*,int) ; 

__attribute__((used)) static void hdmi_unsol_event(struct hda_codec *codec, unsigned int res)
{
	int tag = res >> AC_UNSOL_RES_TAG_SHIFT;
	int subtag = (res & AC_UNSOL_RES_SUBTAG) >> AC_UNSOL_RES_SUBTAG_SHIFT;

	if (codec_has_acomp(codec))
		return;

	if (!snd_hda_jack_tbl_get_from_tag(codec, tag)) {
		codec_dbg(codec, "Unexpected HDMI event tag 0x%x\n", tag);
		return;
	}

	if (subtag == 0)
		hdmi_intrinsic_event(codec, res);
	else
		hdmi_non_intrinsic_event(codec, res);
}