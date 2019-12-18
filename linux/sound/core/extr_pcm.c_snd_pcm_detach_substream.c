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
struct snd_pcm_substream {TYPE_3__* pstr; int /*<<< orphan*/ * pid; TYPE_2__* timer; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {struct snd_pcm_runtime* rules; } ;
struct snd_pcm_runtime {TYPE_1__ hw_constraints; int /*<<< orphan*/  control; int /*<<< orphan*/  status; int /*<<< orphan*/  (* private_free ) (struct snd_pcm_runtime*) ;} ;
struct snd_pcm_mmap_status {int dummy; } ;
struct snd_pcm_mmap_control {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  substream_opened; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_runtime*) ; 

void snd_pcm_detach_substream(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;

	if (PCM_RUNTIME_CHECK(substream))
		return;
	runtime = substream->runtime;
	if (runtime->private_free != NULL)
		runtime->private_free(runtime);
	free_pages_exact(runtime->status,
		       PAGE_ALIGN(sizeof(struct snd_pcm_mmap_status)));
	free_pages_exact(runtime->control,
		       PAGE_ALIGN(sizeof(struct snd_pcm_mmap_control)));
	kfree(runtime->hw_constraints.rules);
	/* Avoid concurrent access to runtime via PCM timer interface */
	if (substream->timer)
		spin_lock_irq(&substream->timer->lock);
	substream->runtime = NULL;
	if (substream->timer)
		spin_unlock_irq(&substream->timer->lock);
	kfree(runtime);
	put_pid(substream->pid);
	substream->pid = NULL;
	substream->pstr->substream_opened--;
}