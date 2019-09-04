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
struct snd_pcm_runtime {int /*<<< orphan*/  fasync; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct file {struct snd_pcm_file* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_fasync(int fd, struct file * file, int on)
{
	struct snd_pcm_file * pcm_file;
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime *runtime;

	pcm_file = file->private_data;
	substream = pcm_file->substream;
	if (PCM_RUNTIME_CHECK(substream))
		return -ENXIO;
	runtime = substream->runtime;
	return fasync_helper(fd, file, on, &runtime->fasync);
}