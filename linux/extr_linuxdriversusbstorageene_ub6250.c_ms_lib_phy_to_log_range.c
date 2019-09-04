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
typedef  int u16 ;

/* Variables and functions */
 int MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT ; 
 int MS_LOGICAL_BLOCKS_PER_SEGMENT ; 
 int MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 

__attribute__((used)) static void ms_lib_phy_to_log_range(u16 PhyBlock, u16 *LogStart, u16 *LogEnde)
{
	PhyBlock /= MS_PHYSICAL_BLOCKS_PER_SEGMENT;

	if (PhyBlock) {
		*LogStart = MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT + (PhyBlock - 1) * MS_LOGICAL_BLOCKS_PER_SEGMENT;/*496*/
		*LogEnde = *LogStart + MS_LOGICAL_BLOCKS_PER_SEGMENT;/*496*/
	} else {
		*LogStart = 0;
		*LogEnde = MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT;/*494*/
	}
}