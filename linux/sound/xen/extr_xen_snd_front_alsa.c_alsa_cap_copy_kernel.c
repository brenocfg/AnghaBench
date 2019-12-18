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
struct xen_snd_front_pcm_stream_info {unsigned long buffer_sz; scalar_t__ buffer; TYPE_1__* evt_pair; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned long) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 scalar_t__ unlikely (int) ; 
 int xen_snd_front_stream_read (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int alsa_cap_copy_kernel(struct snd_pcm_substream *substream,
				int channel, unsigned long pos, void *dst,
				unsigned long count)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	int ret;

	if (unlikely(pos + count > stream->buffer_sz))
		return -EINVAL;

	ret = xen_snd_front_stream_read(&stream->evt_pair->req, pos, count);
	if (ret < 0)
		return ret;

	memcpy(dst, stream->buffer + pos, count);

	return 0;
}