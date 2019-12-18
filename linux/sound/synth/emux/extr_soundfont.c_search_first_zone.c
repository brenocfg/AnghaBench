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
struct snd_sf_zone {int instr; int bank; struct snd_sf_zone* next_instr; } ;
struct snd_sf_list {struct snd_sf_zone** presets; } ;

/* Variables and functions */
 int get_index (int,int,int) ; 

__attribute__((used)) static struct snd_sf_zone *
search_first_zone(struct snd_sf_list *sflist, int bank, int preset, int key)
{
	int index;
	struct snd_sf_zone *zp;

	if ((index = get_index(bank, preset, key)) < 0)
		return NULL;
	for (zp = sflist->presets[index]; zp; zp = zp->next_instr) {
		if (zp->instr == preset && zp->bank == bank)
			return zp;
	}
	return NULL;
}