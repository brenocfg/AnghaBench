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
struct snd_sof_dev {int dummy; } ;
struct snd_dma_buffer {int /*<<< orphan*/ * area; } ;
struct hdac_stream {scalar_t__ format_val; scalar_t__ bufsize; int /*<<< orphan*/ * substream; scalar_t__ running; int /*<<< orphan*/  stream_tag; } ;
struct hdac_ext_stream {struct hdac_stream hstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 int /*<<< orphan*/  HDA_DSP_SPIB_DISABLE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int SOF_HDA_ADSP_REG_CL_SD_BDLPL ; 
 int SOF_HDA_ADSP_REG_CL_SD_BDLPU ; 
 int SOF_STREAM_SD_OFFSET (struct hdac_stream*) ; 
 int /*<<< orphan*/  hda_dsp_stream_put (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hda_dsp_stream_spib_config (struct snd_sof_dev*,struct hdac_ext_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_sof_dsp_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cl_cleanup(struct snd_sof_dev *sdev, struct snd_dma_buffer *dmab,
		      struct hdac_ext_stream *stream)
{
	struct hdac_stream *hstream = &stream->hstream;
	int sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	int ret;

	ret = hda_dsp_stream_spib_config(sdev, stream, HDA_DSP_SPIB_DISABLE, 0);

	hda_dsp_stream_put(sdev, SNDRV_PCM_STREAM_PLAYBACK,
			   hstream->stream_tag);
	hstream->running = 0;
	hstream->substream = NULL;

	/* reset BDL address */
	snd_sof_dsp_write(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL, 0);
	snd_sof_dsp_write(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU, 0);

	snd_sof_dsp_write(sdev, HDA_DSP_HDA_BAR, sd_offset, 0);
	snd_dma_free_pages(dmab);
	dmab->area = NULL;
	hstream->bufsize = 0;
	hstream->format_val = 0;

	return ret;
}