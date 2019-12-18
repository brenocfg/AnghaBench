#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_sof_dev {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct hdac_stream {int dummy; } ;
struct hdac_ext_stream {int dummy; } ;
struct TYPE_2__ {struct hdac_stream* private_data; } ;

/* Variables and functions */
 int hda_dsp_stream_trigger (struct snd_sof_dev*,struct hdac_ext_stream*,int) ; 
 struct hdac_ext_stream* stream_to_hdac_ext_stream (struct hdac_stream*) ; 

int hda_dsp_pcm_trigger(struct snd_sof_dev *sdev,
			struct snd_pcm_substream *substream, int cmd)
{
	struct hdac_stream *hstream = substream->runtime->private_data;
	struct hdac_ext_stream *stream = stream_to_hdac_ext_stream(hstream);

	return hda_dsp_stream_trigger(sdev, stream, cmd);
}