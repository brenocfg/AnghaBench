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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {TYPE_4__* driver; TYPE_1__* component; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct skl_pipe_params {scalar_t__ stream; int link_dma_id; int /*<<< orphan*/  link_bps; int /*<<< orphan*/  format; int /*<<< orphan*/  link_index; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  member_0; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_ext_link {int /*<<< orphan*/  index; } ;
struct hdac_bus {int dummy; } ;
struct TYPE_10__ {int stream_tag; } ;
struct TYPE_8__ {int /*<<< orphan*/  sig_bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  sig_bits; } ;
struct TYPE_9__ {TYPE_3__ capture; TYPE_2__ playback; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDAC_EXT_STREAM_TYPE_LINK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdac_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_5__* hdac_stream (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int skl_tplg_be_update_params (struct snd_soc_dai*,struct skl_pipe_params*) ; 
 struct hdac_ext_link* snd_hdac_ext_bus_get_link (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 struct hdac_ext_stream* snd_hdac_ext_stream_assign (struct hdac_bus*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,void*) ; 
 int /*<<< orphan*/  snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_link_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct hdac_bus *bus = dev_get_drvdata(dai->dev);
	struct hdac_ext_stream *link_dev;
	struct snd_soc_pcm_runtime *rtd = snd_pcm_substream_chip(substream);
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct skl_pipe_params p_params = {0};
	struct hdac_ext_link *link;
	int stream_tag;

	link_dev = snd_hdac_ext_stream_assign(bus, substream,
					HDAC_EXT_STREAM_TYPE_LINK);
	if (!link_dev)
		return -EBUSY;

	snd_soc_dai_set_dma_data(dai, substream, (void *)link_dev);

	link = snd_hdac_ext_bus_get_link(bus, codec_dai->component->name);
	if (!link)
		return -EINVAL;

	stream_tag = hdac_stream(link_dev)->stream_tag;

	/* set the stream tag in the codec dai dma params  */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dai_set_tdm_slot(codec_dai, stream_tag, 0, 0, 0);
	else
		snd_soc_dai_set_tdm_slot(codec_dai, 0, stream_tag, 0, 0);

	p_params.s_fmt = snd_pcm_format_width(params_format(params));
	p_params.ch = params_channels(params);
	p_params.s_freq = params_rate(params);
	p_params.stream = substream->stream;
	p_params.link_dma_id = stream_tag - 1;
	p_params.link_index = link->index;
	p_params.format = params_format(params);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_params.link_bps = codec_dai->driver->playback.sig_bits;
	else
		p_params.link_bps = codec_dai->driver->capture.sig_bits;

	return skl_tplg_be_update_params(dai, &p_params);
}