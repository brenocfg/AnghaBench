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
struct snd_sf_zone {int /*<<< orphan*/  v; struct snd_sf_zone* next; } ;
struct snd_sf_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_voice_info (int /*<<< orphan*/ *) ; 
 struct snd_sf_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_zone_counter (struct snd_sf_list*,struct snd_soundfont*,struct snd_sf_zone*) ; 

__attribute__((used)) static struct snd_sf_zone *
sf_zone_new(struct snd_sf_list *sflist, struct snd_soundfont *sf)
{
	struct snd_sf_zone *zp;

	if ((zp = kzalloc(sizeof(*zp), GFP_KERNEL)) == NULL)
		return NULL;
	zp->next = sf->zones;
	sf->zones = zp;

	init_voice_info(&zp->v);

	set_zone_counter(sflist, sf, zp);
	return zp;
}