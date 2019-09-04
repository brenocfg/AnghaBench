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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct us_data {scalar_t__ extra; } ;
struct ms_lib_type_extdat {int ovrflg; int mngflg; scalar_t__ logadr; } ;
struct TYPE_2__ {scalar_t__ NumberOfPhyBlock; } ;
struct ene_ub6250_info {void** bbuf; TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 scalar_t__ MS_LB_NOT_USED ; 
 scalar_t__ MS_PHYSICAL_BLOCKS_PER_SEGMENT ; 
 int MS_REG_MNG_ATFLG ; 
 int MS_REG_MNG_ATFLG_ATTBL ; 
 int MS_REG_OVR_BKST ; 
 int MS_REG_OVR_BKST_OK ; 
 int MS_REG_OVR_UDST ; 
 int MS_REG_OVR_UDST_UPDATING ; 
#define  MS_STATUS_ERROR 128 
 int MS_STATUS_SUCCESS ; 
 scalar_t__ memstick_logaddr (void*,void*) ; 
 scalar_t__ ms_lib_check_disableblock (struct us_data*,scalar_t__) ; 
 int /*<<< orphan*/  ms_lib_erase_phyblock (struct us_data*,scalar_t__) ; 
 int /*<<< orphan*/  ms_lib_phy_to_log_range (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ms_lib_read_extra (struct us_data*,scalar_t__,int /*<<< orphan*/ ,struct ms_lib_type_extdat*) ; 
 int /*<<< orphan*/  ms_lib_read_extrablock (struct us_data*,scalar_t__,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  ms_lib_set_logicalpair (struct us_data*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ms_lib_setacquired_errorblock (struct us_data*,scalar_t__) ; 
 int ms_libconv_to_logical (struct ene_ub6250_info*,scalar_t__) ; 
 scalar_t__ ms_libconv_to_physical (struct ene_ub6250_info*,scalar_t__) ; 

__attribute__((used)) static int ms_lib_scan_logicalblocknumber(struct us_data *us, u16 btBlk1st)
{
	u16 PhyBlock, newblk, i;
	u16 LogStart, LogEnde;
	struct ms_lib_type_extdat extdat;
	u32 count = 0, index = 0;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	for (PhyBlock = 0; PhyBlock < info->MS_Lib.NumberOfPhyBlock;) {
		ms_lib_phy_to_log_range(PhyBlock, &LogStart, &LogEnde);

		for (i = 0; i < MS_PHYSICAL_BLOCKS_PER_SEGMENT; i++, PhyBlock++) {
			switch (ms_libconv_to_logical(info, PhyBlock)) {
			case MS_STATUS_ERROR:
				continue;
			default:
				break;
			}

			if (count == PhyBlock) {
				ms_lib_read_extrablock(us, PhyBlock, 0, 0x80,
						bbuf);
				count += 0x80;
			}
			index = (PhyBlock % 0x80) * 4;

			extdat.ovrflg = bbuf[index];
			extdat.mngflg = bbuf[index+1];
			extdat.logadr = memstick_logaddr(bbuf[index+2],
					bbuf[index+3]);

			if ((extdat.ovrflg & MS_REG_OVR_BKST) != MS_REG_OVR_BKST_OK) {
				ms_lib_setacquired_errorblock(us, PhyBlock);
				continue;
			}

			if ((extdat.mngflg & MS_REG_MNG_ATFLG) == MS_REG_MNG_ATFLG_ATTBL) {
				ms_lib_erase_phyblock(us, PhyBlock);
				continue;
			}

			if (extdat.logadr != MS_LB_NOT_USED) {
				if ((extdat.logadr < LogStart) || (LogEnde <= extdat.logadr)) {
					ms_lib_erase_phyblock(us, PhyBlock);
					continue;
				}

				newblk = ms_libconv_to_physical(info, extdat.logadr);

				if (newblk != MS_LB_NOT_USED) {
					if (extdat.logadr == 0) {
						ms_lib_set_logicalpair(us, extdat.logadr, PhyBlock);
						if (ms_lib_check_disableblock(us, btBlk1st)) {
							ms_lib_set_logicalpair(us, extdat.logadr, newblk);
							continue;
						}
					}

					ms_lib_read_extra(us, newblk, 0, &extdat);
					if ((extdat.ovrflg & MS_REG_OVR_UDST) == MS_REG_OVR_UDST_UPDATING) {
						ms_lib_erase_phyblock(us, PhyBlock);
						continue;
					} else {
						ms_lib_erase_phyblock(us, newblk);
					}
				}

				ms_lib_set_logicalpair(us, extdat.logadr, PhyBlock);
			}
		}
	} /* End for ... */

	return MS_STATUS_SUCCESS;
}