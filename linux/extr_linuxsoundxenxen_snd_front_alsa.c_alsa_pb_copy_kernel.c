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
struct TYPE_3__ {unsigned long buffer_sz; scalar_t__ buffer; } ;
struct xen_snd_front_pcm_stream_info {TYPE_2__* evt_pair; TYPE_1__ sh_buf; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,unsigned long) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 scalar_t__ unlikely (int) ; 
 int xen_snd_front_stream_write (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int alsa_pb_copy_kernel(struct snd_pcm_substream *substream,
			       int channel, unsigned long pos, void *src,
			       unsigned long count)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	if (unlikely(pos + count > stream->sh_buf.buffer_sz))
		return -EINVAL;

	memcpy(stream->sh_buf.buffer + pos, src, count);

	return xen_snd_front_stream_write(&stream->evt_pair->req, pos, count);
}