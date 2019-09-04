#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {size_t cur_fw_img; } ;
struct iwl_mvm {int dbgfs_sram_offset; int dbgfs_sram_len; TYPE_2__ fwrt; TYPE_1__* fw; } ;
struct fw_img {TYPE_3__* sec; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int offset; int len; } ;
struct TYPE_4__ {struct fw_img* img; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t IWL_UCODE_SECTION_DATA ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int sscanf (char*,char*,int*,int*) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_sram_write(struct iwl_mvm *mvm, char *buf,
				    size_t count, loff_t *ppos)
{
	const struct fw_img *img;
	u32 offset, len;
	u32 img_offset, img_len;

	if (!iwl_mvm_firmware_running(mvm))
		return -EINVAL;

	img = &mvm->fw->img[mvm->fwrt.cur_fw_img];
	img_offset = img->sec[IWL_UCODE_SECTION_DATA].offset;
	img_len = img->sec[IWL_UCODE_SECTION_DATA].len;

	if (sscanf(buf, "%x,%x", &offset, &len) == 2) {
		if ((offset & 0x3) || (len & 0x3))
			return -EINVAL;

		if (offset + len > img_offset + img_len)
			return -EINVAL;

		mvm->dbgfs_sram_offset = offset;
		mvm->dbgfs_sram_len = len;
	} else {
		mvm->dbgfs_sram_offset = 0;
		mvm->dbgfs_sram_len = 0;
	}

	return count;
}