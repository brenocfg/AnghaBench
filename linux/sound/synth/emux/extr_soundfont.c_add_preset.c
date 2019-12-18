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
struct TYPE_2__ {scalar_t__ sf_id; int /*<<< orphan*/  low; } ;
struct snd_sf_zone {scalar_t__ counter; struct snd_sf_zone* next_instr; struct snd_sf_zone* next_zone; TYPE_1__ v; int /*<<< orphan*/  instr; int /*<<< orphan*/  bank; } ;
struct snd_sf_list {struct snd_sf_zone** presets; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_preset (struct snd_sf_list*,struct snd_sf_zone*) ; 
 int get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_sf_zone* search_first_zone (struct snd_sf_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_preset(struct snd_sf_list *sflist, struct snd_sf_zone *cur)
{
	struct snd_sf_zone *zone;
	int index;

	zone = search_first_zone(sflist, cur->bank, cur->instr, cur->v.low);
	if (zone && zone->v.sf_id != cur->v.sf_id) {
		/* different instrument was already defined */
		struct snd_sf_zone *p;
		/* compare the allocated time */
		for (p = zone; p; p = p->next_zone) {
			if (p->counter > cur->counter)
				/* the current is older.. skipped */
				return;
		}
		/* remove old zones */
		delete_preset(sflist, zone);
		zone = NULL; /* do not forget to clear this! */
	}

	/* prepend this zone */
	if ((index = get_index(cur->bank, cur->instr, cur->v.low)) < 0)
		return;
	cur->next_zone = zone; /* zone link */
	cur->next_instr = sflist->presets[index]; /* preset table link */
	sflist->presets[index] = cur;
}