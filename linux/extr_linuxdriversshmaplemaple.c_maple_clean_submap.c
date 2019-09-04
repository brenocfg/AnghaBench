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
struct maple_device {int unit; size_t port; } ;

/* Variables and functions */
 int* subdevice_map ; 

__attribute__((used)) static void maple_clean_submap(struct maple_device *mdev)
{
	int killbit;

	killbit = (mdev->unit > 0 ? (1 << (mdev->unit - 1)) & 0x1f : 0x20);
	killbit = ~killbit;
	killbit &= 0xFF;
	subdevice_map[mdev->port] = subdevice_map[mdev->port] & killbit;
}