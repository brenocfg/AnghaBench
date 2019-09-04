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
struct xen_snd_front_pcm_stream_info {int /*<<< orphan*/  hw_ptr; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t alsa_pointer(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	return (snd_pcm_uframes_t)atomic_read(&stream->hw_ptr);
}