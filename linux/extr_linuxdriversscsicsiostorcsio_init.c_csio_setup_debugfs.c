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
struct csio_hw {TYPE_1__* chip_ops; int /*<<< orphan*/  debugfs_root; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_dfs_create_ext_mem ) (struct csio_hw*) ;} ;

/* Variables and functions */
 int EDRAM0_ENABLE_F ; 
 int EDRAM1_ENABLE_F ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_TARGET_MEM_ENABLE_A ; 
 int /*<<< orphan*/  MEM_EDC0 ; 
 int /*<<< orphan*/  MEM_EDC1 ; 
 int /*<<< orphan*/  csio_add_debugfs_mem (struct csio_hw*,char*,int /*<<< orphan*/ ,int) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct csio_hw*) ; 

__attribute__((used)) static int csio_setup_debugfs(struct csio_hw *hw)
{
	int i;

	if (IS_ERR_OR_NULL(hw->debugfs_root))
		return -1;

	i = csio_rd_reg32(hw, MA_TARGET_MEM_ENABLE_A);
	if (i & EDRAM0_ENABLE_F)
		csio_add_debugfs_mem(hw, "edc0", MEM_EDC0, 5);
	if (i & EDRAM1_ENABLE_F)
		csio_add_debugfs_mem(hw, "edc1", MEM_EDC1, 5);

	hw->chip_ops->chip_dfs_create_ext_mem(hw);
	return 0;
}