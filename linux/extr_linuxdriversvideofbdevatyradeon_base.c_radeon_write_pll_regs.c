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
struct radeonfb_info {scalar_t__ family; scalar_t__ is_mobility; } ;
struct radeon_regs {int ppll_ref_div; int ppll_div_3; int clk_cntl_index; } ;

/* Variables and functions */
 scalar_t__ CHIP_FAMILY_RS300 ; 
 scalar_t__ CHIP_FAMILY_RS400 ; 
 scalar_t__ CHIP_FAMILY_RS480 ; 
 int /*<<< orphan*/  CLOCK_CNTL_INDEX ; 
 int /*<<< orphan*/  HTOTAL_CNTL ; 
 int INPLL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_R300_VARIANT (struct radeonfb_info*) ; 
 int /*<<< orphan*/  OUTPLL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPLLP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OUTREGP (int /*<<< orphan*/ ,int,int) ; 
 int PPLL_ATOMIC_UPDATE_EN ; 
 int PPLL_ATOMIC_UPDATE_R ; 
 int PPLL_ATOMIC_UPDATE_W ; 
 int /*<<< orphan*/  PPLL_CNTL ; 
 int /*<<< orphan*/  PPLL_DIV_3 ; 
 int PPLL_DIV_SEL_MASK ; 
 int PPLL_FB3_DIV_MASK ; 
 int PPLL_POST3_DIV_MASK ; 
 int /*<<< orphan*/  PPLL_REF_DIV ; 
 int PPLL_REF_DIV_MASK ; 
 int PPLL_RESET ; 
 int PPLL_SLEEP ; 
 int PPLL_VGA_ATOMIC_UPDATE_EN ; 
 int R300_PPLL_REF_DIV_ACC_MASK ; 
 int R300_PPLL_REF_DIV_ACC_SHIFT ; 
 int /*<<< orphan*/  VCLK_ECP_CNTL ; 
 int VCLK_SRC_SEL_CPUCLK ; 
 int VCLK_SRC_SEL_MASK ; 
 int VCLK_SRC_SEL_PPLLCLK ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 
 int /*<<< orphan*/  radeon_msleep (int) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_data (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeon_pll_errata_after_index (struct radeonfb_info*) ; 

__attribute__((used)) static void radeon_write_pll_regs(struct radeonfb_info *rinfo, struct radeon_regs *mode)
{
	int i;

	radeon_fifo_wait(20);

	/* Workaround from XFree */
	if (rinfo->is_mobility) {
	        /* A temporal workaround for the occasional blanking on certain laptop
		 * panels. This appears to related to the PLL divider registers
		 * (fail to lock?). It occurs even when all dividers are the same
		 * with their old settings. In this case we really don't need to
		 * fiddle with PLL registers. By doing this we can avoid the blanking
		 * problem with some panels.
	         */
		if ((mode->ppll_ref_div == (INPLL(PPLL_REF_DIV) & PPLL_REF_DIV_MASK)) &&
		    (mode->ppll_div_3 == (INPLL(PPLL_DIV_3) &
					  (PPLL_POST3_DIV_MASK | PPLL_FB3_DIV_MASK)))) {
			/* We still have to force a switch to selected PPLL div thanks to
			 * an XFree86 driver bug which will switch it away in some cases
			 * even when using UseFDev */
			OUTREGP(CLOCK_CNTL_INDEX,
				mode->clk_cntl_index & PPLL_DIV_SEL_MASK,
				~PPLL_DIV_SEL_MASK);
			radeon_pll_errata_after_index(rinfo);
			radeon_pll_errata_after_data(rinfo);
            		return;
		}
	}

	/* Swich VCKL clock input to CPUCLK so it stays fed while PPLL updates*/
	OUTPLLP(VCLK_ECP_CNTL, VCLK_SRC_SEL_CPUCLK, ~VCLK_SRC_SEL_MASK);

	/* Reset PPLL & enable atomic update */
	OUTPLLP(PPLL_CNTL,
		PPLL_RESET | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN,
		~(PPLL_RESET | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN));

	/* Switch to selected PPLL divider */
	OUTREGP(CLOCK_CNTL_INDEX,
		mode->clk_cntl_index & PPLL_DIV_SEL_MASK,
		~PPLL_DIV_SEL_MASK);
	radeon_pll_errata_after_index(rinfo);
	radeon_pll_errata_after_data(rinfo);

	/* Set PPLL ref. div */
	if (IS_R300_VARIANT(rinfo) ||
	    rinfo->family == CHIP_FAMILY_RS300 ||
	    rinfo->family == CHIP_FAMILY_RS400 ||
	    rinfo->family == CHIP_FAMILY_RS480) {
		if (mode->ppll_ref_div & R300_PPLL_REF_DIV_ACC_MASK) {
			/* When restoring console mode, use saved PPLL_REF_DIV
			 * setting.
			 */
			OUTPLLP(PPLL_REF_DIV, mode->ppll_ref_div, 0);
		} else {
			/* R300 uses ref_div_acc field as real ref divider */
			OUTPLLP(PPLL_REF_DIV,
				(mode->ppll_ref_div << R300_PPLL_REF_DIV_ACC_SHIFT), 
				~R300_PPLL_REF_DIV_ACC_MASK);
		}
	} else
		OUTPLLP(PPLL_REF_DIV, mode->ppll_ref_div, ~PPLL_REF_DIV_MASK);

	/* Set PPLL divider 3 & post divider*/
	OUTPLLP(PPLL_DIV_3, mode->ppll_div_3, ~PPLL_FB3_DIV_MASK);
	OUTPLLP(PPLL_DIV_3, mode->ppll_div_3, ~PPLL_POST3_DIV_MASK);

	/* Write update */
	while (INPLL(PPLL_REF_DIV) & PPLL_ATOMIC_UPDATE_R)
		;
	OUTPLLP(PPLL_REF_DIV, PPLL_ATOMIC_UPDATE_W, ~PPLL_ATOMIC_UPDATE_W);

	/* Wait read update complete */
	/* FIXME: Certain revisions of R300 can't recover here.  Not sure of
	   the cause yet, but this workaround will mask the problem for now.
	   Other chips usually will pass at the very first test, so the
	   workaround shouldn't have any effect on them. */
	for (i = 0; (i < 10000 && INPLL(PPLL_REF_DIV) & PPLL_ATOMIC_UPDATE_R); i++)
		;
	
	OUTPLL(HTOTAL_CNTL, 0);

	/* Clear reset & atomic update */
	OUTPLLP(PPLL_CNTL, 0,
		~(PPLL_RESET | PPLL_SLEEP | PPLL_ATOMIC_UPDATE_EN | PPLL_VGA_ATOMIC_UPDATE_EN));

	/* We may want some locking ... oh well */
       	radeon_msleep(5);

	/* Switch back VCLK source to PPLL */
	OUTPLLP(VCLK_ECP_CNTL, VCLK_SRC_SEL_PPLLCLK, ~VCLK_SRC_SEL_MASK);
}