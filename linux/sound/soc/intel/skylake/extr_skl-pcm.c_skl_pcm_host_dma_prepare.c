#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct skl_pipe_params {int /*<<< orphan*/  format; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  host_bps; scalar_t__ host_dma_id; int /*<<< orphan*/  stream; } ;
struct skl_dev {int /*<<< orphan*/  pci; } ;
struct hdac_stream {int dummy; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int prepared; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_BXT (int /*<<< orphan*/ ) ; 
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 
 TYPE_1__* hdac_stream (struct hdac_ext_stream*) ; 
 unsigned int snd_hdac_calc_stream_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_decouple (struct hdac_bus*,struct hdac_ext_stream*,int) ; 
 struct hdac_stream* snd_hdac_get_stream (struct hdac_bus*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_hdac_stream_reset (TYPE_1__*) ; 
 int snd_hdac_stream_set_params (TYPE_1__*,unsigned int) ; 
 int snd_hdac_stream_setup (TYPE_1__*) ; 
 struct hdac_ext_stream* stream_to_hdac_ext_stream (struct hdac_stream*) ; 

int skl_pcm_host_dma_prepare(struct device *dev, struct skl_pipe_params *params)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);
	struct skl_dev *skl = bus_to_skl(bus);
	unsigned int format_val;
	struct hdac_stream *hstream;
	struct hdac_ext_stream *stream;
	int err;

	hstream = snd_hdac_get_stream(bus, params->stream,
					params->host_dma_id + 1);
	if (!hstream)
		return -EINVAL;

	stream = stream_to_hdac_ext_stream(hstream);
	snd_hdac_ext_stream_decouple(bus, stream, true);

	format_val = snd_hdac_calc_stream_format(params->s_freq,
			params->ch, params->format, params->host_bps, 0);

	dev_dbg(dev, "format_val=%d, rate=%d, ch=%d, format=%d\n",
		format_val, params->s_freq, params->ch, params->format);

	snd_hdac_stream_reset(hdac_stream(stream));
	err = snd_hdac_stream_set_params(hdac_stream(stream), format_val);
	if (err < 0)
		return err;

	/*
	 * The recommended SDxFMT programming sequence for BXT
	 * platforms is to couple the stream before writing the format
	 */
	if (IS_BXT(skl->pci)) {
		snd_hdac_ext_stream_decouple(bus, stream, false);
		err = snd_hdac_stream_setup(hdac_stream(stream));
		snd_hdac_ext_stream_decouple(bus, stream, true);
	} else {
		err = snd_hdac_stream_setup(hdac_stream(stream));
	}

	if (err < 0)
		return err;

	hdac_stream(stream)->prepared = 1;

	return 0;
}