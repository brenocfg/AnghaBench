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
struct snd_pcm_substream {scalar_t__ ref_count; int /*<<< orphan*/  (* pcm_release ) (struct snd_pcm_substream*) ;int /*<<< orphan*/  latency_pm_qos_req; scalar_t__ hw_opened; TYPE_3__* ops; TYPE_2__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (struct snd_pcm_substream*) ;int /*<<< orphan*/  (* hw_free ) (struct snd_pcm_substream*) ;} ;
struct TYPE_5__ {TYPE_1__* status; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_qos_request_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_detach_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_drop (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub2 (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub3 (struct snd_pcm_substream*) ; 

void snd_pcm_release_substream(struct snd_pcm_substream *substream)
{
	substream->ref_count--;
	if (substream->ref_count > 0)
		return;

	snd_pcm_drop(substream);
	if (substream->hw_opened) {
		if (substream->ops->hw_free &&
		    substream->runtime->status->state != SNDRV_PCM_STATE_OPEN)
			substream->ops->hw_free(substream);
		substream->ops->close(substream);
		substream->hw_opened = 0;
	}
	if (pm_qos_request_active(&substream->latency_pm_qos_req))
		pm_qos_remove_request(&substream->latency_pm_qos_req);
	if (substream->pcm_release) {
		substream->pcm_release(substream);
		substream->pcm_release = NULL;
	}
	snd_pcm_detach_substream(substream);
}