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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;

/* Variables and functions */
 int EINVAL ; 
 int lock_params (struct snd_pcm_runtime*) ; 
 int snd_pcm_oss_set_subdivide1 (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  unlock_params (struct snd_pcm_runtime*) ; 

__attribute__((used)) static int snd_pcm_oss_set_subdivide(struct snd_pcm_oss_file *pcm_oss_file, int subdivide)
{
	int err = -EINVAL, idx;

	for (idx = 1; idx >= 0; --idx) {
		struct snd_pcm_substream *substream = pcm_oss_file->streams[idx];
		struct snd_pcm_runtime *runtime;

		if (substream == NULL)
			continue;
		runtime = substream->runtime;
		err = lock_params(runtime);
		if (err < 0)
			return err;
		err = snd_pcm_oss_set_subdivide1(substream, subdivide);
		unlock_params(runtime);
		if (err < 0)
			return err;
	}
	return err;
}