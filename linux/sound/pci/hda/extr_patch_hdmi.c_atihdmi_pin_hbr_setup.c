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
 int ATI_HBR_CAPABLE ; 
 int ATI_HBR_ENABLE ; 
 int /*<<< orphan*/  ATI_VERB_GET_HBR_CONTROL ; 
 int /*<<< orphan*/  ATI_VERB_SET_HBR_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atihdmi_pin_hbr_setup(struct hda_codec *codec, hda_nid_t pin_nid,
				 bool hbr)
{
	int hbr_ctl, hbr_ctl_new;

	hbr_ctl = snd_hda_codec_read(codec, pin_nid, 0, ATI_VERB_GET_HBR_CONTROL, 0);
	if (hbr_ctl >= 0 && (hbr_ctl & ATI_HBR_CAPABLE)) {
		if (hbr)
			hbr_ctl_new = hbr_ctl | ATI_HBR_ENABLE;
		else
			hbr_ctl_new = hbr_ctl & ~ATI_HBR_ENABLE;

		codec_dbg(codec,
			  "atihdmi_pin_hbr_setup: NID=0x%x, %shbr-ctl=0x%x\n",
				pin_nid,
				hbr_ctl == hbr_ctl_new ? "" : "new-",
				hbr_ctl_new);

		if (hbr_ctl != hbr_ctl_new)
			snd_hda_codec_write(codec, pin_nid, 0,
						ATI_VERB_SET_HBR_CONTROL,
						hbr_ctl_new);

	} else if (hbr)
		return -EINVAL;

	return 0;
}