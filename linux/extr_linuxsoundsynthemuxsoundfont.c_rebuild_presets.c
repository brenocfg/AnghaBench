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
struct snd_soundfont {struct snd_sf_zone* zones; struct snd_soundfont* next; } ;
struct snd_sf_zone {int /*<<< orphan*/ * sample; int /*<<< orphan*/  v; int /*<<< orphan*/  mapped; struct snd_sf_zone* next; } ;
struct snd_sf_list {struct snd_soundfont* fonts; int /*<<< orphan*/  presets; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_preset (struct snd_sf_list*,struct snd_sf_zone*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * set_sample (struct snd_soundfont*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rebuild_presets(struct snd_sf_list *sflist)
{
	struct snd_soundfont *sf;
	struct snd_sf_zone *cur;

	/* clear preset table */
	memset(sflist->presets, 0, sizeof(sflist->presets));

	/* search all fonts and insert each font */
	for (sf = sflist->fonts; sf; sf = sf->next) {
		for (cur = sf->zones; cur; cur = cur->next) {
			if (! cur->mapped && cur->sample == NULL) {
				/* try again to search the corresponding sample */
				cur->sample = set_sample(sf, &cur->v);
				if (cur->sample == NULL)
					continue;
			}

			add_preset(sflist, cur);
		}
	}
}