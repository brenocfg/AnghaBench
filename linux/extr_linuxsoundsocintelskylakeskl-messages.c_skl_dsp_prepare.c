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
typedef  int /*<<< orphan*/  substream ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct snd_dma_buffer {int dummy; } ;
struct hdac_stream {int stream_tag; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HDAC_EXT_STREAM_TYPE_HOST ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 
 struct hdac_stream* hdac_stream (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  memset (struct snd_pcm_substream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_dsp_setup_spib (struct device*,unsigned int,int,int) ; 
 int snd_hdac_dsp_prepare (struct hdac_stream*,unsigned int,unsigned int,struct snd_dma_buffer*) ; 
 struct hdac_ext_stream* snd_hdac_ext_stream_assign (struct hdac_bus*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_dsp_prepare(struct device *dev, unsigned int format,
			unsigned int size, struct snd_dma_buffer *dmab)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);
	struct hdac_ext_stream *estream;
	struct hdac_stream *stream;
	struct snd_pcm_substream substream;
	int ret;

	if (!bus)
		return -ENODEV;

	memset(&substream, 0, sizeof(substream));
	substream.stream = SNDRV_PCM_STREAM_PLAYBACK;

	estream = snd_hdac_ext_stream_assign(bus, &substream,
					HDAC_EXT_STREAM_TYPE_HOST);
	if (!estream)
		return -ENODEV;

	stream = hdac_stream(estream);

	/* assign decouple host dma channel */
	ret = snd_hdac_dsp_prepare(stream, format, size, dmab);
	if (ret < 0)
		return ret;

	skl_dsp_setup_spib(dev, size, stream->stream_tag, true);

	return stream->stream_tag;
}