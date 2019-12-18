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
struct via82xx {scalar_t__ port; TYPE_1__* devs; } ;
struct TYPE_2__ {unsigned int reg_offset; int shadow_shift; int direction; scalar_t__ port; } ;

/* Variables and functions */

__attribute__((used)) static void init_viadev(struct via82xx *chip, int idx, unsigned int reg_offset,
			int shadow_pos, int direction)
{
	chip->devs[idx].reg_offset = reg_offset;
	chip->devs[idx].shadow_shift = shadow_pos * 4;
	chip->devs[idx].direction = direction;
	chip->devs[idx].port = chip->port + reg_offset;
}