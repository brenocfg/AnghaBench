#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct snd_sof_dev {TYPE_2__ dsp_box; TYPE_1__ stream_box; } ;
struct snd_pcm_substream {TYPE_3__* runtime; } ;
struct intel_stream {int /*<<< orphan*/  posn_offset; } ;
struct TYPE_6__ {struct intel_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  sof_mailbox_read (struct snd_sof_dev*,int /*<<< orphan*/ ,void*,size_t) ; 

void intel_ipc_msg_data(struct snd_sof_dev *sdev,
			struct snd_pcm_substream *substream,
			void *p, size_t sz)
{
	if (!substream || !sdev->stream_box.size) {
		sof_mailbox_read(sdev, sdev->dsp_box.offset, p, sz);
	} else {
		struct intel_stream *stream = substream->runtime->private_data;

		/* The stream might already be closed */
		if (stream)
			sof_mailbox_read(sdev, stream->posn_offset, p, sz);
	}
}