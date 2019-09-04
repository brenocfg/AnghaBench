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
struct TYPE_2__ {int major; } ;
struct ufs_qcom_host {TYPE_1__ hw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_CNTLR_2_x_x_VEN_REGS_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UFS_CNTLR_3_x_x_VEN_REGS_OFFSET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
ufs_qcom_get_debug_reg_offset(struct ufs_qcom_host *host, u32 reg)
{
	if (host->hw_ver.major <= 0x02)
		return UFS_CNTLR_2_x_x_VEN_REGS_OFFSET(reg);

	return UFS_CNTLR_3_x_x_VEN_REGS_OFFSET(reg);
}