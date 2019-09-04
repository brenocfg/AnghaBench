#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int num_memc; scalar_t__ phy_a_standby_ctrl_offs; scalar_t__ phy_b_standby_ctrl_offs; TYPE_1__* memcs; } ;
struct TYPE_3__ {scalar_t__ ddr_phy_base; } ;

/* Variables and functions */
 scalar_t__ DDR_PHY_NO_CHANNEL ; 
 int DDR_PHY_RST_N ; 
 int PWRDWN_SEQ_POWERDOWN_PLL ; 
 int /*<<< orphan*/  SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK ; 
 int SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT ; 
 TYPE_2__ ctrl ; 
 int /*<<< orphan*/  ddr_ctrl_set (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  shimphy_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void s5entry_method1(void)
{
	int i;

	/*
	 * S5 Entry Sequence
	 * -----------------
	 * Step 1: SHIMPHY_ADDR_CNTL_0_DDR_PAD_CNTRL [ S3_PWRDWN_SEQ ] = 3
	 * Step 2: MEMC_DDR_0_WARM_BOOT [ WARM_BOOT ] = 0
	 * Step 3: DDR_PHY_CONTROL_REGS_[AB]_0_STANDBY_CONTROL[ CKE ] = 0
	 *	   DDR_PHY_CONTROL_REGS_[AB]_0_STANDBY_CONTROL[ RST_N ] = 0
	 */
	shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
		    SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
		    ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);

	ddr_ctrl_set(false);

	for (i = 0; i < ctrl.num_memc; i++) {
		u32 tmp;

		/* Step 3: Channel A (RST_N = CKE = 0) */
		tmp = readl_relaxed(ctrl.memcs[i].ddr_phy_base +
				  ctrl.phy_a_standby_ctrl_offs);
		tmp &= ~(DDR_PHY_RST_N | DDR_PHY_RST_N);
		writel_relaxed(tmp, ctrl.memcs[i].ddr_phy_base +
			     ctrl.phy_a_standby_ctrl_offs);

		/* Step 3: Channel B? */
		if (ctrl.phy_b_standby_ctrl_offs != DDR_PHY_NO_CHANNEL) {
			tmp = readl_relaxed(ctrl.memcs[i].ddr_phy_base +
					  ctrl.phy_b_standby_ctrl_offs);
			tmp &= ~(DDR_PHY_RST_N | DDR_PHY_RST_N);
			writel_relaxed(tmp, ctrl.memcs[i].ddr_phy_base +
				     ctrl.phy_b_standby_ctrl_offs);
		}
	}
	/* Must complete */
	wmb();
}