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
struct snd_sf_zone {int dummy; } ;
struct snd_sf_list {int /*<<< orphan*/  lock; scalar_t__ presets_locked; } ;

/* Variables and functions */
 int search_zones (struct snd_sf_list*,int*,int,int,int,struct snd_sf_zone**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snd_soundfont_search_zone(struct snd_sf_list *sflist, int *notep, int vel,
			  int preset, int bank,
			  int def_preset, int def_bank,
			  struct snd_sf_zone **table, int max_layers)
{
	int nvoices;
	unsigned long flags;

	/* this function is supposed to be called atomically,
	 * so we check the lock.  if it's busy, just returns 0 to
	 * tell the caller the busy state
	 */
	spin_lock_irqsave(&sflist->lock, flags);
	if (sflist->presets_locked) {
		spin_unlock_irqrestore(&sflist->lock, flags);
		return 0;
	}
	nvoices = search_zones(sflist, notep, vel, preset, bank,
			       table, max_layers, 0);
	if (! nvoices) {
		if (preset != def_preset || bank != def_bank)
			nvoices = search_zones(sflist, notep, vel,
					       def_preset, def_bank,
					       table, max_layers, 0);
	}
	spin_unlock_irqrestore(&sflist->lock, flags);
	return nvoices;
}