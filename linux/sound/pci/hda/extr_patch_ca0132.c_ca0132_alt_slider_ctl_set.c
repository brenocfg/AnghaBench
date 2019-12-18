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
struct hda_codec {int dummy; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_2__ {scalar_t__ nid; int /*<<< orphan*/ * reqs; int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 int OUT_EFFECTS_COUNT ; 
 scalar_t__ XBASS_XOVER ; 
 scalar_t__ X_BASS ; 
 TYPE_1__* ca0132_effects ; 
 int /*<<< orphan*/  dspio_set_param (struct hda_codec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int const*,int) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 

__attribute__((used)) static int ca0132_alt_slider_ctl_set(struct hda_codec *codec, hda_nid_t nid,
			  const unsigned int *lookup, int idx)
{
	int i = 0;
	unsigned int y;
	/*
	 * For X_BASS, req 2 is actually crossover freq instead of
	 * effect level
	 */
	if (nid == X_BASS)
		y = 2;
	else
		y = 1;

	snd_hda_power_up(codec);
	if (nid == XBASS_XOVER) {
		for (i = 0; i < OUT_EFFECTS_COUNT; i++)
			if (ca0132_effects[i].nid == X_BASS)
				break;

		dspio_set_param(codec, ca0132_effects[i].mid, 0x20,
				ca0132_effects[i].reqs[1],
				&(lookup[idx - 1]), sizeof(unsigned int));
	} else {
		/* Find the actual effect structure */
		for (i = 0; i < OUT_EFFECTS_COUNT; i++)
			if (nid == ca0132_effects[i].nid)
				break;

		dspio_set_param(codec, ca0132_effects[i].mid, 0x20,
				ca0132_effects[i].reqs[y],
				&(lookup[idx]), sizeof(unsigned int));
	}

	snd_hda_power_down(codec);

	return 0;
}