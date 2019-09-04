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
struct snd_sf_list {int presets_locked; int /*<<< orphan*/  lock; int /*<<< orphan*/  presets_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lock_preset(struct snd_sf_list *sflist)
{
	unsigned long flags;
	mutex_lock(&sflist->presets_mutex);
	spin_lock_irqsave(&sflist->lock, flags);
	sflist->presets_locked = 1;
	spin_unlock_irqrestore(&sflist->lock, flags);
}