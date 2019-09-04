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
typedef  unsigned long sector_t ;

/* Variables and functions */
 int sdebug_unmap_alignment ; 
 unsigned long sdebug_unmap_granularity ; 

__attribute__((used)) static sector_t map_index_to_lba(unsigned long index)
{
	sector_t lba = index * sdebug_unmap_granularity;

	if (sdebug_unmap_alignment)
		lba -= sdebug_unmap_granularity - sdebug_unmap_alignment;
	return lba;
}