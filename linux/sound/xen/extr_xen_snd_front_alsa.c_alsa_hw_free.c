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
struct xen_snd_front_pcm_stream_info {TYPE_1__* evt_pair; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  stream_free (struct xen_snd_front_pcm_stream_info*) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int xen_snd_front_stream_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alsa_hw_free(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	int ret;

	ret = xen_snd_front_stream_close(&stream->evt_pair->req);
	stream_free(stream);
	return ret;
}