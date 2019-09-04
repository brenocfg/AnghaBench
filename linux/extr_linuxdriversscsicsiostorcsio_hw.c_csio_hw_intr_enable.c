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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u32 ;
struct csio_hw {scalar_t__ intr_mode; int /*<<< orphan*/  flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIVEC_M ; 
 int /*<<< orphan*/  AIVEC_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_HWF_HW_INTR_ENABLED ; 
 int CSIO_HW_CHIP_MASK ; 
 scalar_t__ CSIO_IM_MSI ; 
 scalar_t__ CSIO_IM_MSIX ; 
 int EGRESS_SIZE_ERR_F ; 
 int ERR_BAD_DB_PIDX0_F ; 
 int ERR_BAD_DB_PIDX1_F ; 
 int ERR_BAD_DB_PIDX2_F ; 
 int ERR_BAD_DB_PIDX3_F ; 
 int ERR_CPL_EXCEED_IQE_SIZE_F ; 
 int ERR_CPL_OPCODE_0_F ; 
 int ERR_DATA_CPL_ON_HIGH_QID0_F ; 
 int ERR_DATA_CPL_ON_HIGH_QID1_F ; 
 int ERR_DROPPED_DB_F ; 
 int ERR_EGR_CTXT_PRIO_F ; 
 int ERR_ING_CTXT_PRIO_F ; 
 int ERR_INVALID_CIDX_INC_F ; 
 int INGRESS_SIZE_ERR_F ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_PF_CFG_A ; 
 int PF_INTR_MASK ; 
 int /*<<< orphan*/  PL_INT_ENABLE_A ; 
 int /*<<< orphan*/  PL_INT_MAP0_A ; 
 int /*<<< orphan*/  PL_PF_INT_ENABLE_A ; 
 int /*<<< orphan*/  PL_WHOAMI_A ; 
 int SF_F ; 
 int /*<<< orphan*/  SGE_INT_ENABLE3_A ; 
 int SOURCEPF_G (int) ; 
 int T6_SOURCEPF_G (int) ; 
 int /*<<< orphan*/  csio_get_mb_intr_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_hw_to_mbm (struct csio_hw*) ; 
 scalar_t__ csio_is_hw_master (struct csio_hw*) ; 
 scalar_t__ csio_is_t5 (int) ; 
 int /*<<< orphan*/  csio_mb_intr_enable (struct csio_hw*) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_reg_field (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_hw_intr_enable(struct csio_hw *hw)
{
	uint16_t vec = (uint16_t)csio_get_mb_intr_idx(csio_hw_to_mbm(hw));
	u32 pf = 0;
	uint32_t pl = csio_rd_reg32(hw, PL_INT_ENABLE_A);

	if (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		pf = SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));
	else
		pf = T6_SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));

	/*
	 * Set aivec for MSI/MSIX. PCIE_PF_CFG.INTXType is set up
	 * by FW, so do nothing for INTX.
	 */
	if (hw->intr_mode == CSIO_IM_MSIX)
		csio_set_reg_field(hw, MYPF_REG(PCIE_PF_CFG_A),
				   AIVEC_V(AIVEC_M), vec);
	else if (hw->intr_mode == CSIO_IM_MSI)
		csio_set_reg_field(hw, MYPF_REG(PCIE_PF_CFG_A),
				   AIVEC_V(AIVEC_M), 0);

	csio_wr_reg32(hw, PF_INTR_MASK, MYPF_REG(PL_PF_INT_ENABLE_A));

	/* Turn on MB interrupts - this will internally flush PIO as well */
	csio_mb_intr_enable(hw);

	/* These are common registers - only a master can modify them */
	if (csio_is_hw_master(hw)) {
		/*
		 * Disable the Serial FLASH interrupt, if enabled!
		 */
		pl &= (~SF_F);
		csio_wr_reg32(hw, pl, PL_INT_ENABLE_A);

		csio_wr_reg32(hw, ERR_CPL_EXCEED_IQE_SIZE_F |
			      EGRESS_SIZE_ERR_F | ERR_INVALID_CIDX_INC_F |
			      ERR_CPL_OPCODE_0_F | ERR_DROPPED_DB_F |
			      ERR_DATA_CPL_ON_HIGH_QID1_F |
			      ERR_DATA_CPL_ON_HIGH_QID0_F | ERR_BAD_DB_PIDX3_F |
			      ERR_BAD_DB_PIDX2_F | ERR_BAD_DB_PIDX1_F |
			      ERR_BAD_DB_PIDX0_F | ERR_ING_CTXT_PRIO_F |
			      ERR_EGR_CTXT_PRIO_F | INGRESS_SIZE_ERR_F,
			      SGE_INT_ENABLE3_A);
		csio_set_reg_field(hw, PL_INT_MAP0_A, 0, 1 << pf);
	}

	hw->flags |= CSIO_HWF_HW_INTR_ENABLED;

}