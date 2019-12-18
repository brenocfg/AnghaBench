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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_dma_buffer {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hdac_stream {unsigned int format_val; unsigned int bufsize; int stream_tag; scalar_t__ period_bytes; int /*<<< orphan*/ * substream; } ;
struct hdac_ext_stream {struct hdac_stream hstream; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HDA_DSP_SPIB_ENABLE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct hdac_ext_stream* hda_dsp_stream_get (struct snd_sof_dev*,int) ; 
 int hda_dsp_stream_hw_params (struct snd_sof_dev*,struct hdac_ext_stream*,struct snd_dma_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hda_dsp_stream_put (struct snd_sof_dev*,int,int) ; 
 int /*<<< orphan*/  hda_dsp_stream_spib_config (struct snd_sof_dev*,struct hdac_ext_stream*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cl_stream_prepare(struct snd_sof_dev *sdev, unsigned int format,
			     unsigned int size, struct snd_dma_buffer *dmab,
			     int direction)
{
	struct hdac_ext_stream *dsp_stream;
	struct hdac_stream *hstream;
	struct pci_dev *pci = to_pci_dev(sdev->dev);
	int ret;

	if (direction != SNDRV_PCM_STREAM_PLAYBACK) {
		dev_err(sdev->dev, "error: code loading DMA is playback only\n");
		return -EINVAL;
	}

	dsp_stream = hda_dsp_stream_get(sdev, direction);

	if (!dsp_stream) {
		dev_err(sdev->dev, "error: no stream available\n");
		return -ENODEV;
	}
	hstream = &dsp_stream->hstream;
	hstream->substream = NULL;

	/* allocate DMA buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV_SG, &pci->dev, size, dmab);
	if (ret < 0) {
		dev_err(sdev->dev, "error: memory alloc failed: %x\n", ret);
		goto error;
	}

	hstream->period_bytes = 0;/* initialize period_bytes */
	hstream->format_val = format;
	hstream->bufsize = size;

	ret = hda_dsp_stream_hw_params(sdev, dsp_stream, dmab, NULL);
	if (ret < 0) {
		dev_err(sdev->dev, "error: hdac prepare failed: %x\n", ret);
		goto error;
	}

	hda_dsp_stream_spib_config(sdev, dsp_stream, HDA_DSP_SPIB_ENABLE, size);

	return hstream->stream_tag;

error:
	hda_dsp_stream_put(sdev, direction, hstream->stream_tag);
	snd_dma_free_pages(dmab);
	return ret;
}