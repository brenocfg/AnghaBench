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
typedef  scalar_t__ u16 ;
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {scalar_t__ NumberOfLogBlock; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 scalar_t__ MS_LB_ERROR ; 
 scalar_t__ MS_LOGICAL_BLOCKS_PER_SEGMENT ; 
 int /*<<< orphan*/  MS_NUMBER_OF_BOOT_BLOCK ; 
 scalar_t__ MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 
 scalar_t__ ms_libconv_to_physical (struct ene_ub6250_info*,scalar_t__) ; 
 int ms_libsearch_block_from_physical (struct us_data*,scalar_t__) ; 

__attribute__((used)) static int ms_libsearch_block_from_logical(struct us_data *us, u16 logblk)
{
	u16 phyblk;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	phyblk = ms_libconv_to_physical(info, logblk);
	if (phyblk >= MS_LB_ERROR) {
		if (logblk >= info->MS_Lib.NumberOfLogBlock)
			return MS_LB_ERROR;

		phyblk = (logblk + MS_NUMBER_OF_BOOT_BLOCK) / MS_LOGICAL_BLOCKS_PER_SEGMENT;
		phyblk *= MS_PHYSICAL_BLOCKS_PER_SEGMENT;
		phyblk += MS_PHYSICAL_BLOCKS_PER_SEGMENT - 1;
	}

	return ms_libsearch_block_from_physical(us, phyblk);
}