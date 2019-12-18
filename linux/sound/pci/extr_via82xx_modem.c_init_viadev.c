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
struct via82xx_modem {scalar_t__ port; TYPE_1__* devs; } ;
struct TYPE_2__ {unsigned int reg_offset; int direction; scalar_t__ port; } ;

/* Variables and functions */

__attribute__((used)) static void init_viadev(struct via82xx_modem *chip, int idx, unsigned int reg_offset,
			int direction)
{
	chip->devs[idx].reg_offset = reg_offset;
	chip->devs[idx].direction = direction;
	chip->devs[idx].port = chip->port + reg_offset;
}