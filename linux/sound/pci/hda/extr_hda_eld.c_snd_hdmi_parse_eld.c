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
struct parsed_hdmi_eld {int eld_ver; int baseline_len; int cea_edid_ver; int support_hdcp; int support_ai; int conn_type; int sad_count; int aud_synch_delay; int spk_alloc; scalar_t__ sad; int /*<<< orphan*/  monitor_name; void* product_id; void* manufacture_id; int /*<<< orphan*/  port_id; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELD_FIXED_BYTES ; 
 int ELD_MAX_MNL ; 
 scalar_t__ ELD_VER_CEA_861D ; 
 scalar_t__ ELD_VER_PARTIAL ; 
 int GRAB_BITS (unsigned char const*,int,int,int) ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,int) ; 
 void* get_unaligned_le16 (unsigned char const*) ; 
 int /*<<< orphan*/  get_unaligned_le64 (unsigned char const*) ; 
 int /*<<< orphan*/  hdmi_update_short_audio_desc (struct hda_codec*,scalar_t__,unsigned char const*) ; 
 int /*<<< orphan*/  memset (struct parsed_hdmi_eld*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 

int snd_hdmi_parse_eld(struct hda_codec *codec, struct parsed_hdmi_eld *e,
			  const unsigned char *buf, int size)
{
	int mnl;
	int i;

	memset(e, 0, sizeof(*e));
	e->eld_ver = GRAB_BITS(buf, 0, 3, 5);
	if (e->eld_ver != ELD_VER_CEA_861D &&
	    e->eld_ver != ELD_VER_PARTIAL) {
		codec_info(codec, "HDMI: Unknown ELD version %d\n", e->eld_ver);
		goto out_fail;
	}

	e->baseline_len = GRAB_BITS(buf, 2, 0, 8);
	mnl		= GRAB_BITS(buf, 4, 0, 5);
	e->cea_edid_ver	= GRAB_BITS(buf, 4, 5, 3);

	e->support_hdcp	= GRAB_BITS(buf, 5, 0, 1);
	e->support_ai	= GRAB_BITS(buf, 5, 1, 1);
	e->conn_type	= GRAB_BITS(buf, 5, 2, 2);
	e->sad_count	= GRAB_BITS(buf, 5, 4, 4);

	e->aud_synch_delay = GRAB_BITS(buf, 6, 0, 8) * 2;
	e->spk_alloc	= GRAB_BITS(buf, 7, 0, 7);

	e->port_id	  = get_unaligned_le64(buf + 8);

	/* not specified, but the spec's tendency is little endian */
	e->manufacture_id = get_unaligned_le16(buf + 16);
	e->product_id	  = get_unaligned_le16(buf + 18);

	if (mnl > ELD_MAX_MNL) {
		codec_info(codec, "HDMI: MNL is reserved value %d\n", mnl);
		goto out_fail;
	} else if (ELD_FIXED_BYTES + mnl > size) {
		codec_info(codec, "HDMI: out of range MNL %d\n", mnl);
		goto out_fail;
	} else
		strlcpy(e->monitor_name, buf + ELD_FIXED_BYTES, mnl + 1);

	for (i = 0; i < e->sad_count; i++) {
		if (ELD_FIXED_BYTES + mnl + 3 * (i + 1) > size) {
			codec_info(codec, "HDMI: out of range SAD %d\n", i);
			goto out_fail;
		}
		hdmi_update_short_audio_desc(codec, e->sad + i,
					buf + ELD_FIXED_BYTES + mnl + 3 * i);
	}

	/*
	 * HDMI sink's ELD info cannot always be retrieved for now, e.g.
	 * in console or for audio devices. Assume the highest speakers
	 * configuration, to _not_ prohibit multi-channel audio playback.
	 */
	if (!e->spk_alloc)
		e->spk_alloc = 0xffff;

	return 0;

out_fail:
	return -EINVAL;
}