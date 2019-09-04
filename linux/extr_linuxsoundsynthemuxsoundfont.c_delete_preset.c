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
struct TYPE_2__ {int /*<<< orphan*/  low; } ;
struct snd_sf_zone {struct snd_sf_zone* next_zone; struct snd_sf_zone* next_instr; TYPE_1__ v; int /*<<< orphan*/  instr; int /*<<< orphan*/  bank; } ;
struct snd_sf_list {struct snd_sf_zone** presets; } ;

/* Variables and functions */
 int get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_preset(struct snd_sf_list *sflist, struct snd_sf_zone *zp)
{
	int index;
	struct snd_sf_zone *p;

	if ((index = get_index(zp->bank, zp->instr, zp->v.low)) < 0)
		return;
	for (p = sflist->presets[index]; p; p = p->next_instr) {
		while (p->next_instr == zp) {
			p->next_instr = zp->next_instr;
			zp = zp->next_zone;
			if (zp == NULL)
				return;
		}
	}
}