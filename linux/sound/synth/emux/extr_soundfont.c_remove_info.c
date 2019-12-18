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
struct snd_soundfont {struct snd_sf_zone* zones; } ;
struct snd_sf_zone {int bank; int instr; struct snd_sf_zone* next; int /*<<< orphan*/  mapped; } ;
struct snd_sf_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sf_zone*) ; 
 int /*<<< orphan*/  rebuild_presets (struct snd_sf_list*) ; 

__attribute__((used)) static int
remove_info(struct snd_sf_list *sflist, struct snd_soundfont *sf,
	    int bank, int instr)
{
	struct snd_sf_zone *prev, *next, *p;
	int removed = 0;

	prev = NULL;
	for (p = sf->zones; p; p = next) {
		next = p->next;
		if (! p->mapped &&
		    p->bank == bank && p->instr == instr) {
			/* remove this layer */
			if (prev)
				prev->next = next;
			else
				sf->zones = next;
			removed++;
			kfree(p);
		} else
			prev = p;
	}
	if (removed)
		rebuild_presets(sflist);
	return removed;
}