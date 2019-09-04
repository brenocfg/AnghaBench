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
typedef  unsigned int const sector_t ;

/* Variables and functions */
 unsigned int const sdebug_sector_size ; 
 unsigned int const sdebug_store_sectors ; 
 scalar_t__ sdebug_virtual_gb ; 

__attribute__((used)) static sector_t get_sdebug_capacity(void)
{
	static const unsigned int gibibyte = 1073741824;

	if (sdebug_virtual_gb > 0)
		return (sector_t)sdebug_virtual_gb *
			(gibibyte / sdebug_sector_size);
	else
		return sdebug_store_sectors;
}