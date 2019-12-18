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
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct snd_pcm_oss_file {int dummy; } ;
struct TYPE_3__ {int period_bytes; } ;
struct TYPE_4__ {TYPE_1__ oss; } ;

/* Variables and functions */
 int snd_pcm_oss_get_active_substream (struct snd_pcm_oss_file*,struct snd_pcm_substream**) ; 

__attribute__((used)) static int snd_pcm_oss_get_block_size(struct snd_pcm_oss_file *pcm_oss_file)
{
	struct snd_pcm_substream *substream;
	int err;
	
	if ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		return err;
	return substream->runtime->oss.period_bytes;
}