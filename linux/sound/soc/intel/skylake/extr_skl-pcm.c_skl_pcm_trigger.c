#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int /*<<< orphan*/  ignore_suspend; } ;
struct snd_soc_dai {struct snd_soc_dapm_widget* capture_widget; struct snd_soc_dapm_widget* playback_widget; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct skl_module_cfg {int /*<<< orphan*/  pipe; } ;
struct skl_dev {int dummy; } ;
struct hdac_ext_stream {int /*<<< orphan*/  lpib; int /*<<< orphan*/  dpib; } ;
struct hdac_bus {int remap_addr; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int AZX_REG_VS_SDXDPIB_XBASE ; 
 int AZX_REG_VS_SDXDPIB_XINTERVAL ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct hdac_bus* get_bus_ctx (struct snd_pcm_substream*) ; 
 struct hdac_ext_stream* get_hdac_ext_stream (struct snd_pcm_substream*) ; 
 struct skl_dev* get_skl_ctx (int /*<<< orphan*/ ) ; 
 TYPE_1__* hdac_stream (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  readl (int) ; 
 int skl_decoupled_trigger (struct snd_pcm_substream*,int) ; 
 int skl_run_pipe (struct skl_dev*,int /*<<< orphan*/ ) ; 
 int skl_stop_pipe (struct skl_dev*,int /*<<< orphan*/ ) ; 
 struct skl_module_cfg* skl_tplg_fe_get_cpr_module (struct snd_soc_dai*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_decouple (struct hdac_bus*,struct hdac_ext_stream*,int) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_drsm_enable (struct hdac_bus*,int,int) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_set_dpibr (struct hdac_bus*,struct hdac_ext_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_set_lpib (struct hdac_ext_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_get_pos_lpib (TYPE_1__*) ; 

__attribute__((used)) static int skl_pcm_trigger(struct snd_pcm_substream *substream, int cmd,
		struct snd_soc_dai *dai)
{
	struct skl_dev *skl = get_skl_ctx(dai->dev);
	struct skl_module_cfg *mconfig;
	struct hdac_bus *bus = get_bus_ctx(substream);
	struct hdac_ext_stream *stream = get_hdac_ext_stream(substream);
	struct snd_soc_dapm_widget *w;
	int ret;

	mconfig = skl_tplg_fe_get_cpr_module(dai, substream->stream);
	if (!mconfig)
		return -EIO;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		w = dai->playback_widget;
	else
		w = dai->capture_widget;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
		if (!w->ignore_suspend) {
			/*
			 * enable DMA Resume enable bit for the stream, set the
			 * dpib & lpib position to resume before starting the
			 * DMA
			 */
			snd_hdac_ext_stream_drsm_enable(bus, true,
						hdac_stream(stream)->index);
			snd_hdac_ext_stream_set_dpibr(bus, stream,
							stream->lpib);
			snd_hdac_ext_stream_set_lpib(stream, stream->lpib);
		}
		/* fall through */

	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * Start HOST DMA and Start FE Pipe.This is to make sure that
		 * there are no underrun/overrun in the case when the FE
		 * pipeline is started but there is a delay in starting the
		 * DMA channel on the host.
		 */
		ret = skl_decoupled_trigger(substream, cmd);
		if (ret < 0)
			return ret;
		return skl_run_pipe(skl, mconfig->pipe);
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
		/*
		 * Stop FE Pipe first and stop DMA. This is to make sure that
		 * there are no underrun/overrun in the case if there is a delay
		 * between the two operations.
		 */
		ret = skl_stop_pipe(skl, mconfig->pipe);
		if (ret < 0)
			return ret;

		ret = skl_decoupled_trigger(substream, cmd);
		if ((cmd == SNDRV_PCM_TRIGGER_SUSPEND) && !w->ignore_suspend) {
			/* save the dpib and lpib positions */
			stream->dpib = readl(bus->remap_addr +
					AZX_REG_VS_SDXDPIB_XBASE +
					(AZX_REG_VS_SDXDPIB_XINTERVAL *
					hdac_stream(stream)->index));

			stream->lpib = snd_hdac_stream_get_pos_lpib(
							hdac_stream(stream));
			snd_hdac_ext_stream_decouple(bus, stream, false);
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}