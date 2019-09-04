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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 unsigned long long U32_MAX ; 
 int ilog2 (unsigned int) ; 

__attribute__((used)) static bool sd_addressable_capacity(u64 lba, unsigned int sector_size)
{
	u64 last_sector = (lba + 1ULL) << (ilog2(sector_size) - 9);

	if (sizeof(sector_t) == 4 && last_sector > U32_MAX)
		return false;

	return true;
}