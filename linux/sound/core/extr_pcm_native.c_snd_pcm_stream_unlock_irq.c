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
struct snd_pcm_substream {TYPE_1__* pcm; int /*<<< orphan*/  self_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  nonatomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_group_unlock_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void snd_pcm_stream_unlock_irq(struct snd_pcm_substream *substream)
{
	snd_pcm_group_unlock_irq(&substream->self_group,
				 substream->pcm->nonatomic);
}