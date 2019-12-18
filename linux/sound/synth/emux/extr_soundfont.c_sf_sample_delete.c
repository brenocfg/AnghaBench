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
struct snd_soundfont {struct snd_sf_sample* samples; } ;
struct snd_sf_sample {struct snd_sf_sample* next; } ;
struct snd_sf_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sf_sample*) ; 

__attribute__((used)) static void
sf_sample_delete(struct snd_sf_list *sflist, struct snd_soundfont *sf,
		 struct snd_sf_sample *sp)
{
	/* only last sample is accepted */
	if (sp == sf->samples) {
		sf->samples = sp->next;
		kfree(sp);
	}
}