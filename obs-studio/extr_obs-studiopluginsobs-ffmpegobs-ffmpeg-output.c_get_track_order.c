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

/* Variables and functions */

__attribute__((used)) static int get_track_order(int track_config, size_t mix_index)
{
	int position = 0;
	for (size_t i = 0; i < mix_index; i++) {
		if (track_config & 1 << i)
			position++;
	}
	return position;
}