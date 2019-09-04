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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_pcm_oss_file*) ; 
 int /*<<< orphan*/  snd_pcm_release_substream (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_oss_release_file(struct snd_pcm_oss_file *pcm_oss_file)
{
	int cidx;
	if (!pcm_oss_file)
		return 0;
	for (cidx = 0; cidx < 2; ++cidx) {
		struct snd_pcm_substream *substream = pcm_oss_file->streams[cidx];
		if (substream)
			snd_pcm_release_substream(substream);
	}
	kfree(pcm_oss_file);
	return 0;
}