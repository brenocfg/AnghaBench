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
typedef  scalar_t__ uint32_t ;
struct fw_debug_cmd {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  pfn; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_PF_MAILBOX_CTRL_A ; 
 int /*<<< orphan*/  CIM_PF_MAILBOX_DATA_A ; 
 int /*<<< orphan*/  CSIO_MBOWNER_FW ; 
 int CSIO_MB_MAX_REGS ; 
 int MBINTREQ_F ; 
 int MBMSGVALID_F ; 
 int MBOWNER_V (int /*<<< orphan*/ ) ; 
 scalar_t__ PF_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_mb_dump_fw_dbg (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,scalar_t__) ; 
 int /*<<< orphan*/  csio_rd_reg64 (struct csio_hw*,scalar_t__) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
csio_mb_debug_cmd_handler(struct csio_hw *hw)
{
	int i;
	__be64 cmd[CSIO_MB_MAX_REGS];
	uint32_t ctl_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_CTRL_A);
	uint32_t data_reg = PF_REG(hw->pfn, CIM_PF_MAILBOX_DATA_A);
	int size = sizeof(struct fw_debug_cmd);

	/* Copy mailbox data */
	for (i = 0; i < size; i += 8)
		cmd[i / 8] = cpu_to_be64(csio_rd_reg64(hw, data_reg + i));

	csio_mb_dump_fw_dbg(hw, cmd);

	/* Notify FW of mailbox by setting owner as UP */
	csio_wr_reg32(hw, MBMSGVALID_F | MBINTREQ_F |
		      MBOWNER_V(CSIO_MBOWNER_FW), ctl_reg);

	csio_rd_reg32(hw, ctl_reg);
	wmb();
}