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
struct hdac_stream {int /*<<< orphan*/  index; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_set_spib (struct hdac_bus*,struct hdac_ext_stream*,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_spbcap_enable (struct hdac_bus*,int,int /*<<< orphan*/ ) ; 
 struct hdac_stream* snd_hdac_get_stream (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 struct hdac_ext_stream* stream_to_hdac_ext_stream (struct hdac_stream*) ; 

__attribute__((used)) static int skl_dsp_setup_spib(struct device *dev, unsigned int size,
				int stream_tag, int enable)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);
	struct hdac_stream *stream = snd_hdac_get_stream(bus,
			SNDRV_PCM_STREAM_PLAYBACK, stream_tag);
	struct hdac_ext_stream *estream;

	if (!stream)
		return -EINVAL;

	estream = stream_to_hdac_ext_stream(stream);
	/* enable/disable SPIB for this hdac stream */
	snd_hdac_ext_stream_spbcap_enable(bus, enable, stream->index);

	/* set the spib value */
	snd_hdac_ext_stream_set_spib(bus, estream, size);

	return 0;
}