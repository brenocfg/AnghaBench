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
struct hda_codec {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_AMPCAP_MIN_MUTE ; 
 int AC_AMPCAP_MUTE ; 
 unsigned int AC_AMP_FAKE_MUTE ; 
 int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 unsigned int snd_hdac_regmap_encode_amp (int /*<<< orphan*/ ,int,int,int) ; 
 int snd_hdac_regmap_update_raw (int /*<<< orphan*/ *,unsigned int,int,int) ; 

int snd_hda_codec_amp_update(struct hda_codec *codec, hda_nid_t nid,
			     int ch, int dir, int idx, int mask, int val)
{
	unsigned int cmd = snd_hdac_regmap_encode_amp(nid, ch, dir, idx);

	/* enable fake mute if no h/w mute but min=mute */
	if ((query_amp_caps(codec, nid, dir) &
	     (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) == AC_AMPCAP_MIN_MUTE)
		cmd |= AC_AMP_FAKE_MUTE;
	return snd_hdac_regmap_update_raw(&codec->core, cmd, mask, val);
}