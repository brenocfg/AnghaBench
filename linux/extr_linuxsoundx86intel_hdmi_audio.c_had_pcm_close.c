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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {scalar_t__ substream_refcount; int /*<<< orphan*/ * substream; } ;
struct snd_intelhad {int /*<<< orphan*/  dev; int /*<<< orphan*/  had_spinlock; TYPE_1__ stream_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int had_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_intelhad *intelhaddata;

	intelhaddata = snd_pcm_substream_chip(substream);

	/* unreference and sync with the pending PCM accesses */
	spin_lock_irq(&intelhaddata->had_spinlock);
	intelhaddata->stream_info.substream = NULL;
	intelhaddata->stream_info.substream_refcount--;
	while (intelhaddata->stream_info.substream_refcount > 0) {
		spin_unlock_irq(&intelhaddata->had_spinlock);
		cpu_relax();
		spin_lock_irq(&intelhaddata->had_spinlock);
	}
	spin_unlock_irq(&intelhaddata->had_spinlock);

	pm_runtime_mark_last_busy(intelhaddata->dev);
	pm_runtime_put_autosuspend(intelhaddata->dev);
	return 0;
}