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
struct snd_soundfont {int type; int /*<<< orphan*/  name; int /*<<< orphan*/ * samples; int /*<<< orphan*/ * zones; struct snd_soundfont* next; int /*<<< orphan*/  id; } ;
struct snd_sf_list {struct snd_soundfont* fonts; int /*<<< orphan*/  fonts_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_SFNT_PATCH_NAME_LEN ; 
 int SNDRV_SFNT_PAT_SHARED ; 
 scalar_t__ is_identical_font (struct snd_soundfont*,int,char*) ; 
 struct snd_soundfont* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soundfont *
newsf(struct snd_sf_list *sflist, int type, char *name)
{
	struct snd_soundfont *sf;

	/* check the shared fonts */
	if (type & SNDRV_SFNT_PAT_SHARED) {
		for (sf = sflist->fonts; sf; sf = sf->next) {
			if (is_identical_font(sf, type, name)) {
				return sf;
			}
		}
	}

	/* not found -- create a new one */
	sf = kzalloc(sizeof(*sf), GFP_KERNEL);
	if (sf == NULL)
		return NULL;
	sf->id = sflist->fonts_size;
	sflist->fonts_size++;

	/* prepend this record */
	sf->next = sflist->fonts;
	sflist->fonts = sf;

	sf->type = type;
	sf->zones = NULL;
	sf->samples = NULL;
	if (name)
		memcpy(sf->name, name, SNDRV_SFNT_PATCH_NAME_LEN);

	return sf;
}