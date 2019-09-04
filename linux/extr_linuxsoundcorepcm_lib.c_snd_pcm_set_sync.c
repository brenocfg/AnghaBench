#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* pcm; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int* id32; } ;
struct snd_pcm_runtime {TYPE_1__ sync; } ;
struct TYPE_6__ {TYPE_2__* card; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */

void snd_pcm_set_sync(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	
	runtime->sync.id32[0] = substream->pcm->card->number;
	runtime->sync.id32[1] = -1;
	runtime->sync.id32[2] = -1;
	runtime->sync.id32[3] = -1;
}