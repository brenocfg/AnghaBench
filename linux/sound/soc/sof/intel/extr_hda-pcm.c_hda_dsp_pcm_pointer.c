#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sof_intel_hda_dev {int /*<<< orphan*/  no_ipc_position; } ;
struct snd_sof_pcm {TYPE_4__* stream; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct snd_soc_pcm_runtime {TYPE_2__* dai_link; } ;
struct snd_pcm_substream {size_t stream; TYPE_5__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct hdac_stream {int index; scalar_t__ bufsize; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_10__ {struct hdac_stream* private_data; } ;
struct TYPE_8__ {scalar_t__ host_posn; } ;
struct TYPE_9__ {TYPE_3__ posn; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 scalar_t__ AZX_REG_VS_SDXDPIB_XBASE ; 
 int AZX_REG_VS_SDXDPIB_XINTERVAL ; 
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ bytes_to_frames (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_stream_get_pos_posbuf (struct hdac_stream*) ; 
 scalar_t__ snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

snd_pcm_uframes_t hda_dsp_pcm_pointer(struct snd_sof_dev *sdev,
				      struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct hdac_stream *hstream = substream->runtime->private_data;
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	struct snd_sof_pcm *spcm;
	snd_pcm_uframes_t pos;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm) {
		dev_warn_ratelimited(sdev->dev, "warn: can't find PCM with DAI ID %d\n",
				     rtd->dai_link->id);
		return 0;
	}

	if (hda && !hda->no_ipc_position) {
		/* read position from IPC position */
		pos = spcm->stream[substream->stream].posn.host_posn;
		goto found;
	}

	/*
	 * DPIB/posbuf position mode:
	 * For Playback, Use DPIB register from HDA space which
	 * reflects the actual data transferred.
	 * For Capture, Use the position buffer for pointer, as DPIB
	 * is not accurate enough, its update may be completed
	 * earlier than the data written to DDR.
	 */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		pos = snd_sof_dsp_read(sdev, HDA_DSP_HDA_BAR,
				       AZX_REG_VS_SDXDPIB_XBASE +
				       (AZX_REG_VS_SDXDPIB_XINTERVAL *
					hstream->index));
	} else {
		/*
		 * For capture stream, we need more workaround to fix the
		 * position incorrect issue:
		 *
		 * 1. Wait at least 20us before reading position buffer after
		 * the interrupt generated(IOC), to make sure position update
		 * happens on frame boundary i.e. 20.833uSec for 48KHz.
		 * 2. Perform a dummy Read to DPIB register to flush DMA
		 * position value.
		 * 3. Read the DMA Position from posbuf. Now the readback
		 * value should be >= period boundary.
		 */
		usleep_range(20, 21);
		snd_sof_dsp_read(sdev, HDA_DSP_HDA_BAR,
				 AZX_REG_VS_SDXDPIB_XBASE +
				 (AZX_REG_VS_SDXDPIB_XINTERVAL *
				  hstream->index));
		pos = snd_hdac_stream_get_pos_posbuf(hstream);
	}

	if (pos >= hstream->bufsize)
		pos = 0;

found:
	pos = bytes_to_frames(substream->runtime, pos);

	dev_vdbg(sdev->dev, "PCM: stream %d dir %d position %lu\n",
		 hstream->index, substream->stream, pos);
	return pos;
}