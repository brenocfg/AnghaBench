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
 int ATI_AUDIODESC_CHANNELS ; 
 int ATI_AUDIODESC_LPCM_STEREO_RATES ; 
 int ATI_AUDIODESC_RATES ; 
 int ATI_DELAY_AUDIO_LATENCY ; 
 int ATI_DELAY_VIDEO_LATENCY ; 
 int ATI_INFO_IDX_MANUFACTURER_ID ; 
 int ATI_INFO_IDX_PORT_ID_HIGH ; 
 int ATI_INFO_IDX_PORT_ID_LOW ; 
 int ATI_INFO_IDX_PRODUCT_ID ; 
 int ATI_INFO_IDX_SINK_DESC_FIRST ; 
 int ATI_INFO_IDX_SINK_DESC_LEN ; 
 int ATI_SPKALLOC_SPKALLOC ; 
 int ATI_SPKALLOC_TYPE_DISPLAYPORT ; 
 int /*<<< orphan*/  ATI_VERB_GET_AUDIO_DESCRIPTOR ; 
 int /*<<< orphan*/  ATI_VERB_GET_AUDIO_VIDEO_DELAY ; 
 int /*<<< orphan*/  ATI_VERB_GET_SINK_INFO_DATA ; 
 int /*<<< orphan*/  ATI_VERB_GET_SPEAKER_ALLOCATION ; 
 int /*<<< orphan*/  ATI_VERB_SET_AUDIO_DESCRIPTOR ; 
 int /*<<< orphan*/  ATI_VERB_SET_SINK_INFO_INDEX ; 
 int AUDIO_CODING_TYPE_DST ; 
 int AUDIO_CODING_TYPE_LPCM ; 
 int AUDIO_CODING_TYPE_SACD ; 
 int AUDIO_CODING_TYPE_WMAPRO ; 
 int EINVAL ; 
 int ELD_FIXED_BYTES ; 
 int ELD_MAX_MNL ; 
 int ELD_MAX_SAD ; 
 int ELD_VER_CEA_861D ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,...) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,unsigned char*) ; 
 int round_up (int,int) ; 
 void* snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_hdmi_get_eld_ati(struct hda_codec *codec, hda_nid_t nid,
			 unsigned char *buf, int *eld_size, bool rev3_or_later)
{
	int spkalloc, ati_sad, aud_synch;
	int sink_desc_len = 0;
	int pos, i;

	/* ATI/AMD does not have ELD, emulate it */

	spkalloc = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SPEAKER_ALLOCATION, 0);

	if (spkalloc <= 0) {
		codec_info(codec, "HDMI ATI/AMD: no speaker allocation for ELD\n");
		return -EINVAL;
	}

	memset(buf, 0, ELD_FIXED_BYTES + ELD_MAX_MNL + ELD_MAX_SAD * 3);

	/* version */
	buf[0] = ELD_VER_CEA_861D << 3;

	/* speaker allocation from EDID */
	buf[7] = spkalloc & ATI_SPKALLOC_SPKALLOC;

	/* is DisplayPort? */
	if (spkalloc & ATI_SPKALLOC_TYPE_DISPLAYPORT)
		buf[5] |= 0x04;

	pos = ELD_FIXED_BYTES;

	if (rev3_or_later) {
		int sink_info;

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PORT_ID_LOW);
		sink_info = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le32(sink_info, buf + 8);

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PORT_ID_HIGH);
		sink_info = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le32(sink_info, buf + 12);

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_MANUFACTURER_ID);
		sink_info = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le16(sink_info, buf + 16);

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PRODUCT_ID);
		sink_info = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le16(sink_info, buf + 18);

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_LEN);
		sink_desc_len = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);

		if (sink_desc_len > ELD_MAX_MNL) {
			codec_info(codec, "HDMI ATI/AMD: Truncating HDMI sink description with length %d\n",
				   sink_desc_len);
			sink_desc_len = ELD_MAX_MNL;
		}

		buf[4] |= sink_desc_len;

		for (i = 0; i < sink_desc_len; i++) {
			snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_FIRST + i);
			buf[pos++] = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		}
	}

	for (i = AUDIO_CODING_TYPE_LPCM; i <= AUDIO_CODING_TYPE_WMAPRO; i++) {
		if (i == AUDIO_CODING_TYPE_SACD || i == AUDIO_CODING_TYPE_DST)
			continue; /* not handled by ATI/AMD */

		snd_hda_codec_write(codec, nid, 0, ATI_VERB_SET_AUDIO_DESCRIPTOR, i << 3);
		ati_sad = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_AUDIO_DESCRIPTOR, 0);

		if (ati_sad <= 0)
			continue;

		if (ati_sad & ATI_AUDIODESC_RATES) {
			/* format is supported, copy SAD as-is */
			buf[pos++] = (ati_sad & 0x0000ff) >> 0;
			buf[pos++] = (ati_sad & 0x00ff00) >> 8;
			buf[pos++] = (ati_sad & 0xff0000) >> 16;
		}

		if (i == AUDIO_CODING_TYPE_LPCM
		    && (ati_sad & ATI_AUDIODESC_LPCM_STEREO_RATES)
		    && (ati_sad & ATI_AUDIODESC_LPCM_STEREO_RATES) >> 16 != (ati_sad & ATI_AUDIODESC_RATES)) {
			/* for PCM there is a separate stereo rate mask */
			buf[pos++] = ((ati_sad & 0x000000ff) & ~ATI_AUDIODESC_CHANNELS) | 0x1;
			/* rates from the extra byte */
			buf[pos++] = (ati_sad & 0xff000000) >> 24;
			buf[pos++] = (ati_sad & 0x00ff0000) >> 16;
		}
	}

	if (pos == ELD_FIXED_BYTES + sink_desc_len) {
		codec_info(codec, "HDMI ATI/AMD: no audio descriptors for ELD\n");
		return -EINVAL;
	}

	/*
	 * HDMI VSDB latency format:
	 * separately for both audio and video:
	 *  0          field not valid or unknown latency
	 *  [1..251]   msecs = (x-1)*2  (max 500ms with x = 251 = 0xfb)
	 *  255        audio/video not supported
	 *
	 * HDA latency format:
	 * single value indicating video latency relative to audio:
	 *  0          unknown or 0ms
	 *  [1..250]   msecs = x*2  (max 500ms with x = 250 = 0xfa)
	 *  [251..255] reserved
	 */
	aud_synch = snd_hda_codec_read(codec, nid, 0, ATI_VERB_GET_AUDIO_VIDEO_DELAY, 0);
	if ((aud_synch & ATI_DELAY_VIDEO_LATENCY) && (aud_synch & ATI_DELAY_AUDIO_LATENCY)) {
		int video_latency_hdmi = (aud_synch & ATI_DELAY_VIDEO_LATENCY);
		int audio_latency_hdmi = (aud_synch & ATI_DELAY_AUDIO_LATENCY) >> 8;

		if (video_latency_hdmi <= 0xfb && audio_latency_hdmi <= 0xfb &&
		    video_latency_hdmi > audio_latency_hdmi)
			buf[6] = video_latency_hdmi - audio_latency_hdmi;
		/* else unknown/invalid or 0ms or video ahead of audio, so use zero */
	}

	/* SAD count */
	buf[5] |= ((pos - ELD_FIXED_BYTES - sink_desc_len) / 3) << 4;

	/* Baseline ELD block length is 4-byte aligned */
	pos = round_up(pos, 4);

	/* Baseline ELD length (4-byte header is not counted in) */
	buf[2] = (pos - 4) / 4;

	*eld_size = pos;

	return 0;
}