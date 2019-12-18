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
struct snd_sf_list {int /*<<< orphan*/  presets_mutex; int /*<<< orphan*/  lock; scalar_t__ presets_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
unlock_preset(struct snd_sf_list *sflist)
{
	unsigned long flags;
	spin_lock_irqsave(&sflist->lock, flags);
	sflist->presets_locked = 0;
	spin_unlock_irqrestore(&sflist->lock, flags);
	mutex_unlock(&sflist->presets_mutex);
}