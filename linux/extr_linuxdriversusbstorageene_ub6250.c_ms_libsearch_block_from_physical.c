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
struct ms_lib_type_extdat {int ovrflg; } ;
struct TYPE_2__ {scalar_t__ NumberOfPhyBlock; scalar_t__* Phy2LogMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
#define  MS_ERROR_FLASH_ERASE 134 
#define  MS_ERROR_FLASH_READ 133 
 int MS_LB_ERROR ; 
 scalar_t__ MS_LB_NOT_USED ; 
 scalar_t__ MS_LB_NOT_USED_ERASED ; 
#define  MS_NOCARD_ERROR 132 
 scalar_t__ MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 
 scalar_t__ MS_PHYSICAL_BLOCKS_PER_SEGMENT_MASK ; 
 int MS_REG_OVR_BKST ; 
 int MS_REG_OVR_BKST_OK ; 
#define  MS_STATUS_ERROR 131 
#define  MS_STATUS_INT_ERROR 130 
#define  MS_STATUS_SUCCESS 129 
#define  MS_STATUS_SUCCESS_WITH_ECC 128 
 int ms_lib_erase_phyblock (struct us_data*,scalar_t__) ; 
 int /*<<< orphan*/  ms_lib_error_phyblock (struct us_data*,scalar_t__) ; 
 int ms_lib_read_extra (struct us_data*,scalar_t__,int /*<<< orphan*/ ,struct ms_lib_type_extdat*) ; 
 int /*<<< orphan*/  ms_lib_setacquired_errorblock (struct us_data*,scalar_t__) ; 

__attribute__((used)) static int ms_libsearch_block_from_physical(struct us_data *us, u16 phyblk)
{
	u16 blk;
	struct ms_lib_type_extdat extdat; /* need check */
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;


	if (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		return MS_LB_ERROR;

	for (blk = phyblk + 1; blk != phyblk; blk++) {
		if ((blk & MS_PHYSICAL_BLOCKS_PER_SEGMENT_MASK) == 0)
			blk -= MS_PHYSICAL_BLOCKS_PER_SEGMENT;

		if (info->MS_Lib.Phy2LogMap[blk] == MS_LB_NOT_USED_ERASED) {
			return blk;
		} else if (info->MS_Lib.Phy2LogMap[blk] == MS_LB_NOT_USED) {
			switch (ms_lib_read_extra(us, blk, 0, &extdat)) {
			case MS_STATUS_SUCCESS:
			case MS_STATUS_SUCCESS_WITH_ECC:
				break;
			case MS_NOCARD_ERROR:
				return MS_NOCARD_ERROR;
			case MS_STATUS_INT_ERROR:
				return MS_LB_ERROR;
			case MS_ERROR_FLASH_READ:
			default:
				ms_lib_setacquired_errorblock(us, blk);
				continue;
			} /* End switch */

			if ((extdat.ovrflg & MS_REG_OVR_BKST) != MS_REG_OVR_BKST_OK) {
				ms_lib_setacquired_errorblock(us, blk);
				continue;
			}

			switch (ms_lib_erase_phyblock(us, blk)) {
			case MS_STATUS_SUCCESS:
				return blk;
			case MS_STATUS_ERROR:
				return MS_LB_ERROR;
			case MS_ERROR_FLASH_ERASE:
			default:
				ms_lib_error_phyblock(us, blk);
				break;
			}
		}
	} /* End for */

	return MS_LB_ERROR;
}