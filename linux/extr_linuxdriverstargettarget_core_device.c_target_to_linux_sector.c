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
struct TYPE_2__ {int block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
typedef  int sector_t ;

/* Variables and functions */

sector_t target_to_linux_sector(struct se_device *dev, sector_t lb)
{
	switch (dev->dev_attrib.block_size) {
	case 4096:
		return lb << 3;
	case 2048:
		return lb << 2;
	case 1024:
		return lb << 1;
	default:
		return lb;
	}
}