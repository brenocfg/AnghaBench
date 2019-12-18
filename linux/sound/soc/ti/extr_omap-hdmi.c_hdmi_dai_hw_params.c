#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_cea_861_aud_if {int db1_ct_cc; int db4_ca; int db5_dminh_lsv; scalar_t__ db3; int /*<<< orphan*/  db2_sf_ss; } ;
struct snd_aes_iec958 {int /*<<< orphan*/ * status; } ;
struct TYPE_6__ {struct snd_cea_861_aud_if* cea; struct snd_aes_iec958* iec; } ;
struct TYPE_4__ {int maxburst; } ;
struct hdmi_audio_data {TYPE_3__ dss_audio; int /*<<< orphan*/  dssdev; TYPE_2__* ops; TYPE_1__ dma_data; struct snd_pcm_substream* current_stream; struct snd_cea_861_aud_if cea; struct snd_aes_iec958 iec; } ;
struct TYPE_5__ {int (* audio_config ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int CEA861_AUDIO_INFOFRAME_DB1CC ; 
 int CEA861_AUDIO_INFOFRAME_DB1CT_FROM_STREAM ; 
 int /*<<< orphan*/  CEA861_AUDIO_INFOFRAME_DB2SF_FROM_STREAM ; 
 int /*<<< orphan*/  CEA861_AUDIO_INFOFRAME_DB2SS_FROM_STREAM ; 
 int CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PERMITTED ; 
 int CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PROHIBITED ; 
 int CEA861_AUDIO_INFOFRAME_DB5_LSV ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEC958_AES0_CON_EMPHASIS_NONE ; 
 int /*<<< orphan*/  IEC958_AES0_CON_NOT_COPYRIGHT ; 
 int /*<<< orphan*/  IEC958_AES0_NONAUDIO ; 
 int /*<<< orphan*/  IEC958_AES0_PROFESSIONAL ; 
 int /*<<< orphan*/  IEC958_AES1_CON_GENERAL ; 
 int /*<<< orphan*/  IEC958_AES2_CON_CHANNEL_UNSPEC ; 
 int /*<<< orphan*/  IEC958_AES2_CON_SOURCE_UNSPEC ; 
 int /*<<< orphan*/  IEC958_AES3_CON_CLOCK_1000PPM ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_176400 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_192000 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_32000 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_44100 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_48000 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_88200 ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS_96000 ; 
 int /*<<< orphan*/  IEC958_AES4_CON_MAX_WORDLEN_24 ; 
 int /*<<< orphan*/  IEC958_AES4_CON_WORDLEN_20_16 ; 
 int /*<<< orphan*/  IEC958_AES4_CON_WORDLEN_24_20 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hdmi_audio_data* card_drvdata_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int hdmi_dai_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params,
			      struct snd_soc_dai *dai)
{
	struct hdmi_audio_data *ad = card_drvdata_substream(substream);
	struct snd_aes_iec958 *iec = &ad->iec;
	struct snd_cea_861_aud_if *cea = &ad->cea;

	WARN_ON(ad->current_stream != substream);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		ad->dma_data.maxburst = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		ad->dma_data.maxburst = 32;
		break;
	default:
		dev_err(dai->dev, "format not supported!\n");
		return -EINVAL;
	}

	ad->dss_audio.iec = iec;
	ad->dss_audio.cea = cea;
	/*
	 * fill the IEC-60958 channel status word
	 */
	/* initialize the word bytes */
	memset(iec->status, 0, sizeof(iec->status));

	/* specify IEC-60958-3 (commercial use) */
	iec->status[0] &= ~IEC958_AES0_PROFESSIONAL;

	/* specify that the audio is LPCM*/
	iec->status[0] &= ~IEC958_AES0_NONAUDIO;

	iec->status[0] |= IEC958_AES0_CON_NOT_COPYRIGHT;

	iec->status[0] |= IEC958_AES0_CON_EMPHASIS_NONE;

	iec->status[1] = IEC958_AES1_CON_GENERAL;

	iec->status[2] |= IEC958_AES2_CON_SOURCE_UNSPEC;

	iec->status[2] |= IEC958_AES2_CON_CHANNEL_UNSPEC;

	switch (params_rate(params)) {
	case 32000:
		iec->status[3] |= IEC958_AES3_CON_FS_32000;
		break;
	case 44100:
		iec->status[3] |= IEC958_AES3_CON_FS_44100;
		break;
	case 48000:
		iec->status[3] |= IEC958_AES3_CON_FS_48000;
		break;
	case 88200:
		iec->status[3] |= IEC958_AES3_CON_FS_88200;
		break;
	case 96000:
		iec->status[3] |= IEC958_AES3_CON_FS_96000;
		break;
	case 176400:
		iec->status[3] |= IEC958_AES3_CON_FS_176400;
		break;
	case 192000:
		iec->status[3] |= IEC958_AES3_CON_FS_192000;
		break;
	default:
		dev_err(dai->dev, "rate not supported!\n");
		return -EINVAL;
	}

	/* specify the clock accuracy */
	iec->status[3] |= IEC958_AES3_CON_CLOCK_1000PPM;

	/*
	 * specify the word length. The same word length value can mean
	 * two different lengths. Hence, we need to specify the maximum
	 * word length as well.
	 */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		iec->status[4] |= IEC958_AES4_CON_WORDLEN_20_16;
		iec->status[4] &= ~IEC958_AES4_CON_MAX_WORDLEN_24;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		iec->status[4] |= IEC958_AES4_CON_WORDLEN_24_20;
		iec->status[4] |= IEC958_AES4_CON_MAX_WORDLEN_24;
		break;
	default:
		dev_err(dai->dev, "format not supported!\n");
		return -EINVAL;
	}

	/*
	 * Fill the CEA-861 audio infoframe (see spec for details)
	 */

	cea->db1_ct_cc = (params_channels(params) - 1)
		& CEA861_AUDIO_INFOFRAME_DB1CC;
	cea->db1_ct_cc |= CEA861_AUDIO_INFOFRAME_DB1CT_FROM_STREAM;

	cea->db2_sf_ss = CEA861_AUDIO_INFOFRAME_DB2SF_FROM_STREAM;
	cea->db2_sf_ss |= CEA861_AUDIO_INFOFRAME_DB2SS_FROM_STREAM;

	cea->db3 = 0; /* not used, all zeros */

	if (params_channels(params) == 2)
		cea->db4_ca = 0x0;
	else if (params_channels(params) == 6)
		cea->db4_ca = 0xb;
	else
		cea->db4_ca = 0x13;

	if (cea->db4_ca == 0x00)
		cea->db5_dminh_lsv = CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PERMITTED;
	else
		cea->db5_dminh_lsv = CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PROHIBITED;

	/* the expression is trivial but makes clear what we are doing */
	cea->db5_dminh_lsv |= (0 & CEA861_AUDIO_INFOFRAME_DB5_LSV);

	return ad->ops->audio_config(ad->dssdev, &ad->dss_audio);
}