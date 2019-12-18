#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;
struct TYPE_4__ {scalar_t__ params; } ;
struct TYPE_3__ {TYPE_2__ oss; } ;

/* Variables and functions */
 int EIO ; 
 int snd_pcm_oss_change_params (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_pcm_oss_get_active_substream(struct snd_pcm_oss_file *pcm_oss_file, struct snd_pcm_substream **r_substream)
{
	int idx, err;
	struct snd_pcm_substream *asubstream = NULL, *substream;

	for (idx = 0; idx < 2; idx++) {
		substream = pcm_oss_file->streams[idx];
		if (substream == NULL)
			continue;
		if (asubstream == NULL)
			asubstream = substream;
		if (substream->runtime->oss.params) {
			err = snd_pcm_oss_change_params(substream, false);
			if (err < 0)
				return err;
		}
	}
	if (!asubstream)
		return -EIO;
	if (r_substream)
		*r_substream = asubstream;
	return 0;
}