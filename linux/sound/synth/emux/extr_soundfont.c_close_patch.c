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
struct snd_sf_list {int open_client; int /*<<< orphan*/  lock; int /*<<< orphan*/ * currsf; } ;

/* Variables and functions */
 int /*<<< orphan*/  rebuild_presets (struct snd_sf_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
close_patch(struct snd_sf_list *sflist)
{
	unsigned long flags;

	spin_lock_irqsave(&sflist->lock, flags);
	sflist->currsf = NULL;
	sflist->open_client = -1;
	spin_unlock_irqrestore(&sflist->lock, flags);

	rebuild_presets(sflist);

	return 0;

}