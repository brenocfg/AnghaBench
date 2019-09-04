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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ufs_hba {int dummy; } ;
typedef  enum unit_desc_param { ____Placeholder_unit_desc_param } unit_desc_param ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_UNIT ; 
 int /*<<< orphan*/  ufs_is_valid_unit_desc_lun (int) ; 
 int ufshcd_read_desc_param (struct ufs_hba*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ufshcd_read_unit_desc_param(struct ufs_hba *hba,
					      int lun,
					      enum unit_desc_param param_offset,
					      u8 *param_read_buf,
					      u32 param_size)
{
	/*
	 * Unit descriptors are only available for general purpose LUs (LUN id
	 * from 0 to 7) and RPMB Well known LU.
	 */
	if (!ufs_is_valid_unit_desc_lun(lun))
		return -EOPNOTSUPP;

	return ufshcd_read_desc_param(hba, QUERY_DESC_IDN_UNIT, lun,
				      param_offset, param_read_buf, param_size);
}