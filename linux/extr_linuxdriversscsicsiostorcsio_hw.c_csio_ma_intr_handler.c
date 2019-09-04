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
typedef  int uint32_t ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_INT_CAUSE_A ; 
 int /*<<< orphan*/  MA_INT_WRAP_STATUS_A ; 
 int /*<<< orphan*/  MA_PARITY_ERROR_STATUS_A ; 
 int MEM_PERR_INT_CAUSE_F ; 
 int MEM_WRAP_ADDRESS_G (int) ; 
 int /*<<< orphan*/  MEM_WRAP_CLIENT_NUM_G (int) ; 
 int MEM_WRAP_INT_CAUSE_F ; 
 int /*<<< orphan*/  csio_fatal (struct csio_hw*,char*,int,...) ; 
 int /*<<< orphan*/  csio_hw_fatal_err (struct csio_hw*) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csio_ma_intr_handler(struct csio_hw *hw)
{
	uint32_t v, status = csio_rd_reg32(hw, MA_INT_CAUSE_A);

	if (status & MEM_PERR_INT_CAUSE_F)
		csio_fatal(hw, "MA parity error, parity status %#x\n",
			    csio_rd_reg32(hw, MA_PARITY_ERROR_STATUS_A));
	if (status & MEM_WRAP_INT_CAUSE_F) {
		v = csio_rd_reg32(hw, MA_INT_WRAP_STATUS_A);
		csio_fatal(hw,
		   "MA address wrap-around error by client %u to address %#x\n",
		   MEM_WRAP_CLIENT_NUM_G(v), MEM_WRAP_ADDRESS_G(v) << 4);
	}
	csio_wr_reg32(hw, status, MA_INT_CAUSE_A);
	csio_hw_fatal_err(hw);
}