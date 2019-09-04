#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct idma_ctrl {int state; } ;
struct TYPE_2__ {struct idma_ctrl* private_data; } ;

/* Variables and functions */
 int ST_RUNNING ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static void idma_done(void *id, int bytes_xfer)
{
	struct snd_pcm_substream *substream = id;
	struct idma_ctrl *prtd = substream->runtime->private_data;

	if (prtd && (prtd->state & ST_RUNNING))
		snd_pcm_period_elapsed(substream);
}