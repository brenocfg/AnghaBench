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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct us_data {scalar_t__ extra; } ;
struct ms_lib_type_extdat {int dummy; } ;
struct TYPE_2__ {size_t* Log2PhyMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MS_BYTES_PER_PAGE ; 
 size_t MS_ERROR_FLASH_READ ; 
 size_t MS_LB_NOT_USED ; 
 size_t MS_NO_MEMORY_ERROR ; 
 size_t MS_STATUS_SUCCESS ; 
 size_t be16_to_cpu (unsigned char) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_read_readpage (struct us_data*,size_t,int,int /*<<< orphan*/ *,struct ms_lib_type_extdat*) ; 

__attribute__((used)) static int ms_lib_check_disableblock(struct us_data *us, u16 PhyBlock)
{
	unsigned char *PageBuf = NULL;
	u16 result = MS_STATUS_SUCCESS;
	u16 blk, index = 0;
	struct ms_lib_type_extdat extdat;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	PageBuf = kmalloc(MS_BYTES_PER_PAGE, GFP_KERNEL);
	if (PageBuf == NULL) {
		result = MS_NO_MEMORY_ERROR;
		goto exit;
	}

	ms_read_readpage(us, PhyBlock, 1, (u32 *)PageBuf, &extdat);
	do {
		blk = be16_to_cpu(PageBuf[index]);
		if (blk == MS_LB_NOT_USED)
			break;
		if (blk == info->MS_Lib.Log2PhyMap[0]) {
			result = MS_ERROR_FLASH_READ;
			break;
		}
		index++;
	} while (1);

exit:
	kfree(PageBuf);
	return result;
}