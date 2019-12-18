#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_stream_posn {int dummy; } ;
struct sof_ipc_pcm_params_reply {size_t posn_offset; } ;
struct TYPE_4__ {size_t size; size_t offset; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; TYPE_2__ stream_box; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; TYPE_1__* runtime; } ;
struct intel_stream {size_t posn_offset; } ;
struct TYPE_3__ {struct intel_stream* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 

int intel_ipc_pcm_params(struct snd_sof_dev *sdev,
			 struct snd_pcm_substream *substream,
			 const struct sof_ipc_pcm_params_reply *reply)
{
	struct intel_stream *stream = substream->runtime->private_data;
	size_t posn_offset = reply->posn_offset;

	/* check if offset is overflow or it is not aligned */
	if (posn_offset > sdev->stream_box.size ||
	    posn_offset % sizeof(struct sof_ipc_stream_posn) != 0)
		return -EINVAL;

	stream->posn_offset = sdev->stream_box.offset + posn_offset;

	dev_dbg(sdev->dev, "pcm: stream dir %d, posn mailbox offset is %zu",
		substream->stream, stream->posn_offset);

	return 0;
}