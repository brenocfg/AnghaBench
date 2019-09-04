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
struct snd_soundfont {int type; } ;
struct snd_sf_sample {scalar_t__ counter; } ;
struct snd_sf_list {scalar_t__ sample_counter; scalar_t__ sample_locked; } ;

/* Variables and functions */
 int SNDRV_SFNT_PAT_LOCKED ; 

__attribute__((used)) static void
set_sample_counter(struct snd_sf_list *sflist, struct snd_soundfont *sf,
		   struct snd_sf_sample *sp)
{
	sp->counter = sflist->sample_counter++;
	if (sf->type & SNDRV_SFNT_PAT_LOCKED)
		sflist->sample_locked = sflist->sample_counter;
}