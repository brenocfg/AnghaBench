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
struct vx_pipe {int /*<<< orphan*/  position; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct vx_pipe* private_data; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */

__attribute__((used)) static snd_pcm_uframes_t vx_pcm_playback_pointer(struct snd_pcm_substream *subs)
{
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct vx_pipe *pipe = runtime->private_data;
	return pipe->position;
}