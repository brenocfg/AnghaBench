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
struct snd_pcm_substream {int /*<<< orphan*/  self_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_group_assign (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock (struct snd_pcm_substream*) ; 

__attribute__((used)) static void relink_to_local(struct snd_pcm_substream *substream)
{
	snd_pcm_stream_lock(substream);
	snd_pcm_group_assign(substream, &substream->self_group);
	snd_pcm_stream_unlock(substream);
}