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
typedef  void* u32 ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int EXT_MEM1_ENABLE_F ; 
 int EXT_MEM_ENABLE_F ; 
 int /*<<< orphan*/  EXT_MEM_SIZE_G (void*) ; 
 int /*<<< orphan*/  MA_EXT_MEMORY1_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY_BAR_A ; 
 int /*<<< orphan*/  MA_TARGET_MEM_ENABLE_A ; 
 int /*<<< orphan*/  MEM_MC0 ; 
 int /*<<< orphan*/  MEM_MC1 ; 
 int /*<<< orphan*/  csio_add_debugfs_mem (struct csio_hw*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_t5_dfs_create_ext_mem(struct csio_hw *hw)
{
	u32 size;
	int i = csio_rd_reg32(hw, MA_TARGET_MEM_ENABLE_A);

	if (i & EXT_MEM_ENABLE_F) {
		size = csio_rd_reg32(hw, MA_EXT_MEMORY_BAR_A);
		csio_add_debugfs_mem(hw, "mc0", MEM_MC0,
				     EXT_MEM_SIZE_G(size));
	}
	if (i & EXT_MEM1_ENABLE_F) {
		size = csio_rd_reg32(hw, MA_EXT_MEMORY1_BAR_A);
		csio_add_debugfs_mem(hw, "mc1", MEM_MC1,
				     EXT_MEM_SIZE_G(size));
	}
}