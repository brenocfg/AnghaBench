#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soundfont {struct snd_sf_zone* samples; struct snd_sf_zone* zones; struct snd_soundfont* next; } ;
struct TYPE_3__ {scalar_t__ truesize; } ;
struct snd_sf_zone {scalar_t__ counter; TYPE_1__ v; struct snd_sf_zone* next; } ;
struct snd_sf_sample {scalar_t__ counter; TYPE_1__ v; struct snd_sf_sample* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* sample_free ) (int /*<<< orphan*/ ,struct snd_sf_zone*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sample_reset ) (int /*<<< orphan*/ ) ;} ;
struct snd_sf_list {scalar_t__ zone_locked; scalar_t__ sample_locked; scalar_t__ zone_counter; scalar_t__ sample_counter; int /*<<< orphan*/  memhdr; TYPE_2__ callback; int /*<<< orphan*/  mem_used; struct snd_soundfont* fonts; int /*<<< orphan*/  presets; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sf_zone*) ; 
 int /*<<< orphan*/  lock_preset (struct snd_sf_list*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rebuild_presets (struct snd_sf_list*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct snd_sf_zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_preset (struct snd_sf_list*) ; 

int
snd_soundfont_remove_unlocked(struct snd_sf_list *sflist)
{
	struct snd_soundfont *sf;
	struct snd_sf_zone *zp, *nextzp;
	struct snd_sf_sample *sp, *nextsp;

	lock_preset(sflist);

	if (sflist->callback.sample_reset)
		sflist->callback.sample_reset(sflist->callback.private_data);

	/* to be sure */
	memset(sflist->presets, 0, sizeof(sflist->presets));

	for (sf = sflist->fonts; sf; sf = sf->next) {
		for (zp = sf->zones; zp; zp = nextzp) {
			if (zp->counter < sflist->zone_locked)
				break;
			nextzp = zp->next;
			sf->zones = nextzp;
			kfree(zp);
		}

		for (sp = sf->samples; sp; sp = nextsp) {
			if (sp->counter < sflist->sample_locked)
				break;
			nextsp = sp->next;
			sf->samples = nextsp;
			sflist->mem_used -= sp->v.truesize;
			if (sflist->callback.sample_free)
				sflist->callback.sample_free(sflist->callback.private_data,
							     sp, sflist->memhdr);
			kfree(sp);
		}
	}

	sflist->zone_counter = sflist->zone_locked;
	sflist->sample_counter = sflist->sample_locked;

	rebuild_presets(sflist);

	unlock_preset(sflist);
	return 0;
}