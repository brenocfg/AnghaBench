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
struct xen_snd_front_pcm_stream_info {int /*<<< orphan*/  evt_pair; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  xen_snd_front_evtchnl_pair_set_connected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alsa_close(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	xen_snd_front_evtchnl_pair_set_connected(stream->evt_pair, false);
	return 0;
}