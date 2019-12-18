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
typedef  int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * bar; } ;
struct hdac_stream {int index; } ;
struct hdac_ext_stream {int /*<<< orphan*/  spib_addr; struct hdac_stream hstream; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HDA_DSP_SPIB_BAR ; 
 int /*<<< orphan*/  SOF_HDA_ADSP_REG_CL_SPBFIFO_SPBFCCTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sof_io_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int) ; 

int hda_dsp_stream_spib_config(struct snd_sof_dev *sdev,
			       struct hdac_ext_stream *stream,
			       int enable, u32 size)
{
	struct hdac_stream *hstream = &stream->hstream;
	u32 mask;

	if (!sdev->bar[HDA_DSP_SPIB_BAR]) {
		dev_err(sdev->dev, "error: address of spib capability is NULL\n");
		return -EINVAL;
	}

	mask = (1 << hstream->index);

	/* enable/disable SPIB for the stream */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_SPIB_BAR,
				SOF_HDA_ADSP_REG_CL_SPBFIFO_SPBFCCTL, mask,
				enable << hstream->index);

	/* set the SPIB value */
	sof_io_write(sdev, stream->spib_addr, size);

	return 0;
}