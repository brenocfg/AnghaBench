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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {int* Phy2LogMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
#define  MS_LB_NOT_USED 129 
#define  MS_LB_NOT_USED_ERASED 128 
 size_t MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 

__attribute__((used)) static int ms_count_freeblock(struct us_data *us, u16 PhyBlock)
{
	u32 Ende, Count;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	Ende = PhyBlock + MS_PHYSICAL_BLOCKS_PER_SEGMENT;
	for (Count = 0; PhyBlock < Ende; PhyBlock++) {
		switch (info->MS_Lib.Phy2LogMap[PhyBlock]) {
		case MS_LB_NOT_USED:
		case MS_LB_NOT_USED_ERASED:
			Count++;
		default:
			break;
		}
	}

	return Count;
}