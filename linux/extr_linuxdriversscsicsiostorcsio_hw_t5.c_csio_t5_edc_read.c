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
 int /*<<< orphan*/  EDC_BIST_STATUS_RDATA_A ; 
 int EDC_BIST_STATUS_REG (int /*<<< orphan*/ ,int) ; 
 int EDC_H_BIST_CMD_A ; 
 int EDC_H_BIST_CMD_ADDR_A ; 
 int EDC_H_BIST_CMD_LEN_A ; 
 int EDC_H_BIST_DATA_PATTERN_A ; 
 int EDC_H_BIST_STATUS_RDATA_A ; 
 int EDC_T50_BASE_ADDR ; 
 int EDC_T51_BASE_ADDR ; 
 int START_BIST_F ; 
 int csio_hw_wait_op_done_val (struct csio_hw*,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int csio_rd_reg32 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_rd_reg64 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int) ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static int
csio_t5_edc_read(struct csio_hw *hw, int idx, uint32_t addr, __be32 *data,
		uint64_t *ecc)
{
	int i;
	uint32_t edc_bist_cmd_reg, edc_bist_cmd_addr_reg, edc_bist_cmd_len_reg;
	uint32_t edc_bist_cmd_data_pattern, edc_bist_status_rdata_reg;

/*
 * These macro are missing in t4_regs.h file.
 */
#define EDC_STRIDE_T5 (EDC_T51_BASE_ADDR - EDC_T50_BASE_ADDR)
#define EDC_REG_T5(reg, idx) (reg + EDC_STRIDE_T5 * idx)

	edc_bist_cmd_reg = EDC_REG_T5(EDC_H_BIST_CMD_A, idx);
	edc_bist_cmd_addr_reg = EDC_REG_T5(EDC_H_BIST_CMD_ADDR_A, idx);
	edc_bist_cmd_len_reg = EDC_REG_T5(EDC_H_BIST_CMD_LEN_A, idx);
	edc_bist_cmd_data_pattern = EDC_REG_T5(EDC_H_BIST_DATA_PATTERN_A, idx);
	edc_bist_status_rdata_reg = EDC_REG_T5(EDC_H_BIST_STATUS_RDATA_A, idx);
#undef EDC_REG_T5
#undef EDC_STRIDE_T5

	if (csio_rd_reg32(hw, edc_bist_cmd_reg) & START_BIST_F)
		return -EBUSY;
	csio_wr_reg32(hw, addr & ~0x3fU, edc_bist_cmd_addr_reg);
	csio_wr_reg32(hw, 64, edc_bist_cmd_len_reg);
	csio_wr_reg32(hw, 0xc, edc_bist_cmd_data_pattern);
	csio_wr_reg32(hw, BIST_OPCODE_V(1) | START_BIST_F |  BIST_CMD_GAP_V(1),
		      edc_bist_cmd_reg);
	i = csio_hw_wait_op_done_val(hw, edc_bist_cmd_reg, START_BIST_F,
				     0, 10, 1, NULL);
	if (i)
		return i;

#define EDC_DATA(i) (EDC_BIST_STATUS_REG(EDC_BIST_STATUS_RDATA_A, i) + idx)

	for (i = 15; i >= 0; i--)
		*data++ = htonl(csio_rd_reg32(hw, EDC_DATA(i)));
	if (ecc)
		*ecc = csio_rd_reg64(hw, EDC_DATA(16));
#undef EDC_DATA
	return 0;
}