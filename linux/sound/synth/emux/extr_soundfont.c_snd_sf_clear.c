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
struct snd_soundfont {struct snd_soundfont* next; struct snd_soundfont* samples; struct snd_soundfont* zones; } ;
struct snd_sf_zone {struct snd_sf_zone* next; struct snd_sf_zone* samples; struct snd_sf_zone* zones; } ;
struct snd_sf_sample {struct snd_sf_sample* next; struct snd_sf_sample* samples; struct snd_sf_sample* zones; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* sample_free ) (int /*<<< orphan*/ ,struct snd_soundfont*,int /*<<< orphan*/ ) ;} ;
struct snd_sf_list {int /*<<< orphan*/  memhdr; TYPE_1__ callback; struct snd_soundfont* fonts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_soundfont*) ; 
 int /*<<< orphan*/  snd_sf_init (struct snd_sf_list*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct snd_soundfont*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_sf_clear(struct snd_sf_list *sflist)
{
	struct snd_soundfont *sf, *nextsf;
	struct snd_sf_zone *zp, *nextzp;
	struct snd_sf_sample *sp, *nextsp;

	for (sf = sflist->fonts; sf; sf = nextsf) {
		nextsf = sf->next;
		for (zp = sf->zones; zp; zp = nextzp) {
			nextzp = zp->next;
			kfree(zp);
		}
		for (sp = sf->samples; sp; sp = nextsp) {
			nextsp = sp->next;
			if (sflist->callback.sample_free)
				sflist->callback.sample_free(sflist->callback.private_data,
							     sp, sflist->memhdr);
			kfree(sp);
		}
		kfree(sf);
	}

	snd_sf_init(sflist);
}