#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_info_entry {struct hda_codec* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {unsigned int afg; } ;
struct hda_codec {int /*<<< orphan*/  (* proc_widget_hook ) (struct snd_info_buffer*,struct hda_codec*,unsigned int) ;scalar_t__ dp_mst; scalar_t__ pin_amp_workaround; scalar_t__ single_adc_amp; int /*<<< orphan*/  nids; int /*<<< orphan*/  mixers; TYPE_1__ core; } ;
typedef  unsigned int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_AUDIO_WIDGET_CAP ; 
 unsigned int AC_WCAP_CONN_LIST ; 
 unsigned int AC_WCAP_CP_CAPS ; 
 unsigned int AC_WCAP_DELAY ; 
 unsigned int AC_WCAP_DELAY_SHIFT ; 
 unsigned int AC_WCAP_DIGITAL ; 
 unsigned int AC_WCAP_FORMAT_OVRD ; 
 unsigned int AC_WCAP_IN_AMP ; 
 unsigned int AC_WCAP_LR_SWAP ; 
 unsigned int AC_WCAP_OUT_AMP ; 
 unsigned int AC_WCAP_POWER ; 
 unsigned int AC_WCAP_PROC_WID ; 
 unsigned int AC_WCAP_STEREO ; 
 unsigned int AC_WCAP_STRIPE ; 
 unsigned int AC_WCAP_UNSOL_CAP ; 
#define  AC_WID_AUD_IN 131 
#define  AC_WID_AUD_OUT 130 
#define  AC_WID_PIN 129 
#define  AC_WID_VOL_KNB 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 unsigned int get_wcaps_channels (unsigned int) ; 
 unsigned int get_wcaps_type (unsigned int) ; 
 int /*<<< orphan*/  get_wid_type_name (unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 unsigned int param_read (struct hda_codec*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_amp_caps (struct snd_info_buffer*,struct hda_codec*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_amp_vals (struct snd_info_buffer*,struct hda_codec*,unsigned int,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  print_audio_io (struct snd_info_buffer*,struct hda_codec*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  print_codec_core_info (TYPE_1__*,struct snd_info_buffer*) ; 
 int /*<<< orphan*/  print_conn_list (struct snd_info_buffer*,struct hda_codec*,unsigned int,unsigned int,unsigned int*,int) ; 
 int /*<<< orphan*/  print_device_list (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_digital_conv (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_gpio (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_nid_array (struct snd_info_buffer*,struct hda_codec*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_nid_pcms (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_pcm_caps (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_pin_caps (struct snd_info_buffer*,struct hda_codec*,unsigned int,int*) ; 
 int /*<<< orphan*/  print_pin_ctls (struct snd_info_buffer*,struct hda_codec*,unsigned int,int) ; 
 int /*<<< orphan*/  print_power_state (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_proc_caps (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_unsol_cap (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  print_vol_knob (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int snd_hda_get_num_raw_conns (struct hda_codec*,unsigned int) ; 
 scalar_t__ snd_hda_get_raw_connections (struct hda_codec*,unsigned int,unsigned int*,int) ; 
 int snd_hda_get_sub_nodes (struct hda_codec*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct snd_info_buffer*,struct hda_codec*,unsigned int) ; 

__attribute__((used)) static void print_codec_info(struct snd_info_entry *entry,
			     struct snd_info_buffer *buffer)
{
	struct hda_codec *codec = entry->private_data;
	hda_nid_t nid, fg;
	int i, nodes;

	print_codec_core_info(&codec->core, buffer);
	fg = codec->core.afg;
	if (!fg)
		return;
	snd_hda_power_up(codec);
	snd_iprintf(buffer, "Default PCM:\n");
	print_pcm_caps(buffer, codec, fg);
	snd_iprintf(buffer, "Default Amp-In caps: ");
	print_amp_caps(buffer, codec, fg, HDA_INPUT);
	snd_iprintf(buffer, "Default Amp-Out caps: ");
	print_amp_caps(buffer, codec, fg, HDA_OUTPUT);
	snd_iprintf(buffer, "State of AFG node 0x%02x:\n", fg);
	print_power_state(buffer, codec, fg);

	nodes = snd_hda_get_sub_nodes(codec, fg, &nid);
	if (! nid || nodes < 0) {
		snd_iprintf(buffer, "Invalid AFG subtree\n");
		snd_hda_power_down(codec);
		return;
	}

	print_gpio(buffer, codec, fg);
	if (codec->proc_widget_hook)
		codec->proc_widget_hook(buffer, codec, fg);

	for (i = 0; i < nodes; i++, nid++) {
		unsigned int wid_caps =
			param_read(codec, nid, AC_PAR_AUDIO_WIDGET_CAP);
		unsigned int wid_type = get_wcaps_type(wid_caps);
		hda_nid_t *conn = NULL;
		int conn_len = 0;

		snd_iprintf(buffer, "Node 0x%02x [%s] wcaps 0x%x:", nid,
			    get_wid_type_name(wid_type), wid_caps);
		if (wid_caps & AC_WCAP_STEREO) {
			unsigned int chans = get_wcaps_channels(wid_caps);
			if (chans == 2)
				snd_iprintf(buffer, " Stereo");
			else
				snd_iprintf(buffer, " %d-Channels", chans);
		} else
			snd_iprintf(buffer, " Mono");
		if (wid_caps & AC_WCAP_DIGITAL)
			snd_iprintf(buffer, " Digital");
		if (wid_caps & AC_WCAP_IN_AMP)
			snd_iprintf(buffer, " Amp-In");
		if (wid_caps & AC_WCAP_OUT_AMP)
			snd_iprintf(buffer, " Amp-Out");
		if (wid_caps & AC_WCAP_STRIPE)
			snd_iprintf(buffer, " Stripe");
		if (wid_caps & AC_WCAP_LR_SWAP)
			snd_iprintf(buffer, " R/L");
		if (wid_caps & AC_WCAP_CP_CAPS)
			snd_iprintf(buffer, " CP");
		snd_iprintf(buffer, "\n");

		print_nid_array(buffer, codec, nid, &codec->mixers);
		print_nid_array(buffer, codec, nid, &codec->nids);
		print_nid_pcms(buffer, codec, nid);

		/* volume knob is a special widget that always have connection
		 * list
		 */
		if (wid_type == AC_WID_VOL_KNB)
			wid_caps |= AC_WCAP_CONN_LIST;

		if (wid_caps & AC_WCAP_CONN_LIST) {
			conn_len = snd_hda_get_num_raw_conns(codec, nid);
			if (conn_len > 0) {
				conn = kmalloc_array(conn_len,
						     sizeof(hda_nid_t),
						     GFP_KERNEL);
				if (!conn)
					return;
				if (snd_hda_get_raw_connections(codec, nid, conn,
								conn_len) < 0)
					conn_len = 0;
			}
		}

		if (wid_caps & AC_WCAP_IN_AMP) {
			snd_iprintf(buffer, "  Amp-In caps: ");
			print_amp_caps(buffer, codec, nid, HDA_INPUT);
			snd_iprintf(buffer, "  Amp-In vals: ");
			if (wid_type == AC_WID_PIN ||
			    (codec->single_adc_amp &&
			     wid_type == AC_WID_AUD_IN))
				print_amp_vals(buffer, codec, nid, HDA_INPUT,
					       wid_caps, 1);
			else
				print_amp_vals(buffer, codec, nid, HDA_INPUT,
					       wid_caps, conn_len);
		}
		if (wid_caps & AC_WCAP_OUT_AMP) {
			snd_iprintf(buffer, "  Amp-Out caps: ");
			print_amp_caps(buffer, codec, nid, HDA_OUTPUT);
			snd_iprintf(buffer, "  Amp-Out vals: ");
			if (wid_type == AC_WID_PIN &&
			    codec->pin_amp_workaround)
				print_amp_vals(buffer, codec, nid, HDA_OUTPUT,
					       wid_caps, conn_len);
			else
				print_amp_vals(buffer, codec, nid, HDA_OUTPUT,
					       wid_caps, 1);
		}

		switch (wid_type) {
		case AC_WID_PIN: {
			int supports_vref;
			print_pin_caps(buffer, codec, nid, &supports_vref);
			print_pin_ctls(buffer, codec, nid, supports_vref);
			break;
		}
		case AC_WID_VOL_KNB:
			print_vol_knob(buffer, codec, nid);
			break;
		case AC_WID_AUD_OUT:
		case AC_WID_AUD_IN:
			print_audio_io(buffer, codec, nid, wid_type);
			if (wid_caps & AC_WCAP_DIGITAL)
				print_digital_conv(buffer, codec, nid);
			if (wid_caps & AC_WCAP_FORMAT_OVRD) {
				snd_iprintf(buffer, "  PCM:\n");
				print_pcm_caps(buffer, codec, nid);
			}
			break;
		}

		if (wid_caps & AC_WCAP_UNSOL_CAP)
			print_unsol_cap(buffer, codec, nid);

		if (wid_caps & AC_WCAP_POWER)
			print_power_state(buffer, codec, nid);

		if (wid_caps & AC_WCAP_DELAY)
			snd_iprintf(buffer, "  Delay: %d samples\n",
				    (wid_caps & AC_WCAP_DELAY) >>
				    AC_WCAP_DELAY_SHIFT);

		if (wid_type == AC_WID_PIN && codec->dp_mst)
			print_device_list(buffer, codec, nid);

		if (wid_caps & AC_WCAP_CONN_LIST)
			print_conn_list(buffer, codec, nid, wid_type,
					conn, conn_len);

		if (wid_caps & AC_WCAP_PROC_WID)
			print_proc_caps(buffer, codec, nid);

		if (codec->proc_widget_hook)
			codec->proc_widget_hook(buffer, codec, nid);

		kfree(conn);
	}
	snd_hda_power_down(codec);
}