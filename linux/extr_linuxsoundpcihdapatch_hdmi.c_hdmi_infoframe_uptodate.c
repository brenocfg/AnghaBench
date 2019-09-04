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
typedef  scalar_t__ u8 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ AC_DIPXMIT_BEST ; 
 int /*<<< orphan*/  AC_VERB_GET_HDMI_DIP_DATA ; 
 int /*<<< orphan*/  AC_VERB_GET_HDMI_DIP_XMIT ; 
 int /*<<< orphan*/  hdmi_set_dip_index (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hdmi_infoframe_uptodate(struct hda_codec *codec, hda_nid_t pin_nid,
				    u8 *dip, int size)
{
	u8 val;
	int i;

	if (snd_hda_codec_read(codec, pin_nid, 0, AC_VERB_GET_HDMI_DIP_XMIT, 0)
							    != AC_DIPXMIT_BEST)
		return false;

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	for (i = 0; i < size; i++) {
		val = snd_hda_codec_read(codec, pin_nid, 0,
					 AC_VERB_GET_HDMI_DIP_DATA, 0);
		if (val != dip[i])
			return false;
	}

	return true;
}