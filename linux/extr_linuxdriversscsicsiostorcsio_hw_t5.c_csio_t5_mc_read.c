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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct csio_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int BIST_CMD_GAP_V (int) ; 
 int BIST_OPCODE_V (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  MC_BIST_STATUS_RDATA_A ; 
 int MC_BIST_STATUS_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MC_P_BIST_CMD_A ; 
 int /*<<< orphan*/  MC_P_BIST_CMD_ADDR_A ; 
 int /*<<< orphan*/  MC_P_BIST_CMD_LEN_A ; 
 int /*<<< orphan*/  MC_P_BIST_DATA_PATTERN_A ; 
 int /*<<< orphan*/  MC_P_BIST_STATUS_RDATA_A ; 
 int MC_REG (int /*<<< orphan*/ ,int) ; 
 int START_BIST_F ; 
 int csio_hw_wait_op_done_val (struct csio_hw*,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int csio_rd_reg32 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_rd_reg64 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int) ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static int
csio_t5_mc_read(struct csio_hw *hw, int idx, uint32_t addr, __be32 *data,
		uint64_t *ecc)
{
	int i;
	uint32_t mc_bist_cmd_reg, mc_bist_cmd_addr_reg, mc_bist_cmd_len_reg;
	uint32_t mc_bist_status_rdata_reg, mc_bist_data_pattern_reg;

	mc_bist_cmd_reg = MC_REG(MC_P_BIST_CMD_A, idx);
	mc_bist_cmd_addr_reg = MC_REG(MC_P_BIST_CMD_ADDR_A, idx);
	mc_bist_cmd_len_reg = MC_REG(MC_P_BIST_CMD_LEN_A, idx);
	mc_bist_status_rdata_reg = MC_REG(MC_P_BIST_STATUS_RDATA_A, idx);
	mc_bist_data_pattern_reg = MC_REG(MC_P_BIST_DATA_PATTERN_A, idx);

	if (csio_rd_reg32(hw, mc_bist_cmd_reg) & START_BIST_F)
		return -EBUSY;
	csio_wr_reg32(hw, addr & ~0x3fU, mc_bist_cmd_addr_reg);
	csio_wr_reg32(hw, 64, mc_bist_cmd_len_reg);
	csio_wr_reg32(hw, 0xc, mc_bist_data_pattern_reg);
	csio_wr_reg32(hw, BIST_OPCODE_V(1) | START_BIST_F |  BIST_CMD_GAP_V(1),
		      mc_bist_cmd_reg);
	i = csio_hw_wait_op_done_val(hw, mc_bist_cmd_reg, START_BIST_F,
				     0, 10, 1, NULL);
	if (i)
		return i;

#define MC_DATA(i) MC_BIST_STATUS_REG(MC_BIST_STATUS_RDATA_A, i)

	for (i = 15; i >= 0; i--)
		*data++ = htonl(csio_rd_reg32(hw, MC_DATA(i)));
	if (ecc)
		*ecc = csio_rd_reg64(hw, MC_DATA(16));
#undef MC_DATA
	return 0;
}