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

__attribute__((used)) static unsigned int ad7280a_devaddr(unsigned int addr)
{
	return ((addr & 0x1) << 4) |
	       ((addr & 0x2) << 3) |
	       (addr & 0x4) |
	       ((addr & 0x8) >> 3) |
	       ((addr & 0x10) >> 4);
}