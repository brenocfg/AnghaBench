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
struct kbd_state {int level; scalar_t__ mode_bit; } ;
struct TYPE_2__ {scalar_t__ levels; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ kbd_info ; 
 scalar_t__* kbd_mode_levels ; 
 int kbd_mode_levels_count ; 

__attribute__((used)) static int kbd_get_level(struct kbd_state *state)
{
	int i;

	if (kbd_info.levels != 0)
		return state->level;

	if (kbd_mode_levels_count > 0) {
		for (i = 0; i < kbd_mode_levels_count; ++i)
			if (kbd_mode_levels[i] == state->mode_bit)
				return i;
		return 0;
	}

	return -EINVAL;
}