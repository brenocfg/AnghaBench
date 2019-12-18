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
struct snd_sf_list {int open_client; scalar_t__ sample_locked; scalar_t__ zone_locked; scalar_t__ sample_counter; scalar_t__ zone_counter; scalar_t__ fonts_size; int /*<<< orphan*/ * fonts; int /*<<< orphan*/ * currsf; scalar_t__ mem_used; int /*<<< orphan*/  presets; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
snd_sf_init(struct snd_sf_list *sflist)
{
	memset(sflist->presets, 0, sizeof(sflist->presets));

	sflist->mem_used = 0;
	sflist->currsf = NULL;
	sflist->open_client = -1;
	sflist->fonts = NULL;
	sflist->fonts_size = 0;
	sflist->zone_counter = 0;
	sflist->sample_counter = 0;
	sflist->zone_locked = 0;
	sflist->sample_locked = 0;
}