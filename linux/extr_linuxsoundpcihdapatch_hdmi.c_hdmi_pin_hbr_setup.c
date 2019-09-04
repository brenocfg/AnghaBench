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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_PINCAP_HBR ; 
 int AC_PINCTL_EPT ; 
 int AC_PINCTL_EPT_HBR ; 
 int AC_PINCTL_EPT_NATIVE ; 
 int /*<<< orphan*/  AC_VERB_GET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_pin_hbr_setup(struct hda_codec *codec, hda_nid_t pin_nid,
			      bool hbr)
{
	int pinctl, new_pinctl;

	if (snd_hda_query_pin_caps(codec, pin_nid) & AC_PINCAP_HBR) {
		pinctl = snd_hda_codec_read(codec, pin_nid, 0,
					    AC_VERB_GET_PIN_WIDGET_CONTROL, 0);

		if (pinctl < 0)
			return hbr ? -EINVAL : 0;

		new_pinctl = pinctl & ~AC_PINCTL_EPT;
		if (hbr)
			new_pinctl |= AC_PINCTL_EPT_HBR;
		else
			new_pinctl |= AC_PINCTL_EPT_NATIVE;

		codec_dbg(codec,
			  "hdmi_pin_hbr_setup: NID=0x%x, %spinctl=0x%x\n",
			    pin_nid,
			    pinctl == new_pinctl ? "" : "new-",
			    new_pinctl);

		if (pinctl != new_pinctl)
			snd_hda_codec_write(codec, pin_nid, 0,
					    AC_VERB_SET_PIN_WIDGET_CONTROL,
					    new_pinctl);
	} else if (hbr)
		return -EINVAL;

	return 0;
}