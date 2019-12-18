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
struct xen_snd_front_pcm_stream_info {unsigned long buffer_sz; TYPE_1__* evt_pair; scalar_t__ buffer; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 scalar_t__ unlikely (int) ; 
 int xen_snd_front_stream_write (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int alsa_pb_fill_silence(struct snd_pcm_substream *substream,
				int channel, unsigned long pos,
				unsigned long count)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	if (unlikely(pos + count > stream->buffer_sz))
		return -EINVAL;

	memset(stream->buffer + pos, 0, count);

	return xen_snd_front_stream_write(&stream->evt_pair->req, pos, count);
}