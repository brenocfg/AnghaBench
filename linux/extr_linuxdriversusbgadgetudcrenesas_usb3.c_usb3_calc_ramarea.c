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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PN_RAMMAP_RAMAREA_16KB ; 
 int /*<<< orphan*/  PN_RAMMAP_RAMAREA_1KB ; 
 int /*<<< orphan*/  PN_RAMMAP_RAMAREA_2KB ; 
 int /*<<< orphan*/  PN_RAMMAP_RAMAREA_4KB ; 
 int /*<<< orphan*/  PN_RAMMAP_RAMAREA_8KB ; 
 int SZ_16K ; 
 int SZ_1K ; 
 int SZ_2K ; 
 int SZ_4K ; 
 int SZ_8K ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u32 usb3_calc_ramarea(int ram_size)
{
	WARN_ON(ram_size > SZ_16K);

	if (ram_size <= SZ_1K)
		return PN_RAMMAP_RAMAREA_1KB;
	else if (ram_size <= SZ_2K)
		return PN_RAMMAP_RAMAREA_2KB;
	else if (ram_size <= SZ_4K)
		return PN_RAMMAP_RAMAREA_4KB;
	else if (ram_size <= SZ_8K)
		return PN_RAMMAP_RAMAREA_8KB;
	else
		return PN_RAMMAP_RAMAREA_16KB;
}