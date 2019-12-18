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
struct dp_audio_infoframe {int type; int len; int ver; int CC02_CT47; int CA; } ;
struct hdmi_audio_infoframe {int type; int ver; int len; int CC02_CT47; int CA; } ;
union audio_infoframe {int /*<<< orphan*/  bytes; struct dp_audio_infoframe dp; struct hdmi_audio_infoframe hdmi; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
typedef  int /*<<< orphan*/  ai ;

/* Variables and functions */
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  hdmi_checksum_audio_infoframe (struct hdmi_audio_infoframe*) ; 
 int /*<<< orphan*/  hdmi_fill_audio_infoframe (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_infoframe_uptodate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_start_infoframe_trans (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_stop_infoframe_trans (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union audio_infoframe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_pin_setup_infoframe(struct hda_codec *codec,
				     hda_nid_t pin_nid,
				     int ca, int active_channels,
				     int conn_type)
{
	union audio_infoframe ai;

	memset(&ai, 0, sizeof(ai));
	if (conn_type == 0) { /* HDMI */
		struct hdmi_audio_infoframe *hdmi_ai = &ai.hdmi;

		hdmi_ai->type		= 0x84;
		hdmi_ai->ver		= 0x01;
		hdmi_ai->len		= 0x0a;
		hdmi_ai->CC02_CT47	= active_channels - 1;
		hdmi_ai->CA		= ca;
		hdmi_checksum_audio_infoframe(hdmi_ai);
	} else if (conn_type == 1) { /* DisplayPort */
		struct dp_audio_infoframe *dp_ai = &ai.dp;

		dp_ai->type		= 0x84;
		dp_ai->len		= 0x1b;
		dp_ai->ver		= 0x11 << 2;
		dp_ai->CC02_CT47	= active_channels - 1;
		dp_ai->CA		= ca;
	} else {
		codec_dbg(codec, "HDMI: unknown connection type at pin %d\n",
			    pin_nid);
		return;
	}

	/*
	 * sizeof(ai) is used instead of sizeof(*hdmi_ai) or
	 * sizeof(*dp_ai) to avoid partial match/update problems when
	 * the user switches between HDMI/DP monitors.
	 */
	if (!hdmi_infoframe_uptodate(codec, pin_nid, ai.bytes,
					sizeof(ai))) {
		codec_dbg(codec,
			  "hdmi_pin_setup_infoframe: pin=%d channels=%d ca=0x%02x\n",
			    pin_nid,
			    active_channels, ca);
		hdmi_stop_infoframe_trans(codec, pin_nid);
		hdmi_fill_audio_infoframe(codec, pin_nid,
					    ai.bytes, sizeof(ai));
		hdmi_start_infoframe_trans(codec, pin_nid);
	}
}