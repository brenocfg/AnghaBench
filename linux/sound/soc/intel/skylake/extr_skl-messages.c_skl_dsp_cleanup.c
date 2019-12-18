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
struct snd_dma_buffer {int dummy; } ;
struct hdac_stream {int dummy; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HDAC_EXT_STREAM_TYPE_HOST ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  skl_dsp_setup_spib (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_hdac_dsp_cleanup (struct hdac_stream*,struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_release (struct hdac_ext_stream*,int /*<<< orphan*/ ) ; 
 struct hdac_stream* snd_hdac_get_stream (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 struct hdac_ext_stream* stream_to_hdac_ext_stream (struct hdac_stream*) ; 

__attribute__((used)) static int skl_dsp_cleanup(struct device *dev,
		struct snd_dma_buffer *dmab, int stream_tag)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);
	struct hdac_stream *stream;
	struct hdac_ext_stream *estream;

	if (!bus)
		return -ENODEV;

	stream = snd_hdac_get_stream(bus,
		SNDRV_PCM_STREAM_PLAYBACK, stream_tag);
	if (!stream)
		return -EINVAL;

	estream = stream_to_hdac_ext_stream(stream);
	skl_dsp_setup_spib(dev, 0, stream_tag, false);
	snd_hdac_ext_stream_release(estream, HDAC_EXT_STREAM_TYPE_HOST);

	snd_hdac_dsp_cleanup(stream, dmab);

	return 0;
}