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
typedef  int u32 ;
struct q6v5 {scalar_t__ version; int /*<<< orphan*/  dev; scalar_t__ reg_base; scalar_t__ rmb_base; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BOOT_FSM_TIMEOUT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HALT_CHECK_MAX_LOOPS ; 
 scalar_t__ MSS_MSM8996 ; 
 scalar_t__ MSS_SDM845 ; 
 int Q6SS_BUS_ARES_ENABLE ; 
 int Q6SS_CLAMP_IO ; 
 int Q6SS_CLK_ENABLE ; 
 int Q6SS_CORE_ARES ; 
 int Q6SS_ETB_SLP_NRET_N ; 
 int Q6SS_L2DATA_SLP_NRET_N_0 ; 
 int Q6SS_L2DATA_SLP_NRET_N_1 ; 
 int Q6SS_L2DATA_SLP_NRET_N_2 ; 
 int Q6SS_L2DATA_STBY_N ; 
 int Q6SS_L2TAG_SLP_NRET_N ; 
 int Q6SS_SLP_RET_N ; 
 int Q6SS_STOP_CORE ; 
 int QDSP6SS_ACC_OVERRIDE_VAL ; 
 scalar_t__ QDSP6SS_BOOT_CMD ; 
 scalar_t__ QDSP6SS_BOOT_CORE_START ; 
 scalar_t__ QDSP6SS_GFMUX_CTL_REG ; 
 scalar_t__ QDSP6SS_MEM_PWR_CTL ; 
 scalar_t__ QDSP6SS_PWR_CTL_REG ; 
 scalar_t__ QDSP6SS_RESET_REG ; 
 scalar_t__ QDSP6SS_SLEEP ; 
 scalar_t__ QDSP6SS_STRAP_ACC ; 
 scalar_t__ QDSP6SS_XO_CBCR ; 
 int QDSP6v56_BHS_ON ; 
 int QDSP6v56_CLAMP_QMC_MEM ; 
 int QDSP6v56_CLAMP_WL ; 
 int QDSP6v56_LDO_BYP ; 
 int QDSS_BHS_ON ; 
 int QDSS_LDO_BYP ; 
 scalar_t__ RMB_MBA_MSS_STATUS ; 
 int RMB_PBL_SUCCESS ; 
 int /*<<< orphan*/  SLEEP_CHECK_MAX_LOOPS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  q6v5_reset_deassert (struct q6v5*) ; 
 int q6v5_rmb_pbl_wait (struct q6v5*,int) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int q6v5proc_reset(struct q6v5 *qproc)
{
	u32 val;
	int ret;
	int i;

	if (qproc->version == MSS_SDM845) {
		val = readl(qproc->reg_base + QDSP6SS_SLEEP);
		val |= 0x1;
		writel(val, qproc->reg_base + QDSP6SS_SLEEP);

		ret = readl_poll_timeout(qproc->reg_base + QDSP6SS_SLEEP,
					 val, !(val & BIT(31)), 1,
					 SLEEP_CHECK_MAX_LOOPS);
		if (ret) {
			dev_err(qproc->dev, "QDSP6SS Sleep clock timed out\n");
			return -ETIMEDOUT;
		}

		/* De-assert QDSP6 stop core */
		writel(1, qproc->reg_base + QDSP6SS_BOOT_CORE_START);
		/* Trigger boot FSM */
		writel(1, qproc->reg_base + QDSP6SS_BOOT_CMD);

		ret = readl_poll_timeout(qproc->rmb_base + RMB_MBA_MSS_STATUS,
				val, (val & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
		if (ret) {
			dev_err(qproc->dev, "Boot FSM failed to complete.\n");
			/* Reset the modem so that boot FSM is in reset state */
			q6v5_reset_deassert(qproc);
			return ret;
		}

		goto pbl_wait;
	} else if (qproc->version == MSS_MSM8996) {
		/* Override the ACC value if required */
		writel(QDSP6SS_ACC_OVERRIDE_VAL,
		       qproc->reg_base + QDSP6SS_STRAP_ACC);

		/* Assert resets, stop core */
		val = readl(qproc->reg_base + QDSP6SS_RESET_REG);
		val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
		writel(val, qproc->reg_base + QDSP6SS_RESET_REG);

		/* BHS require xo cbcr to be enabled */
		val = readl(qproc->reg_base + QDSP6SS_XO_CBCR);
		val |= 0x1;
		writel(val, qproc->reg_base + QDSP6SS_XO_CBCR);

		/* Read CLKOFF bit to go low indicating CLK is enabled */
		ret = readl_poll_timeout(qproc->reg_base + QDSP6SS_XO_CBCR,
					 val, !(val & BIT(31)), 1,
					 HALT_CHECK_MAX_LOOPS);
		if (ret) {
			dev_err(qproc->dev,
				"xo cbcr enabling timed out (rc:%d)\n", ret);
			return ret;
		}
		/* Enable power block headswitch and wait for it to stabilize */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= QDSP6v56_BHS_ON;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		udelay(1);

		/* Put LDO in bypass mode */
		val |= QDSP6v56_LDO_BYP;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Deassert QDSP6 compiler memory clamp */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val &= ~QDSP6v56_CLAMP_QMC_MEM;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Deassert memory peripheral sleep and L2 memory standby */
		val |= Q6SS_L2DATA_STBY_N | Q6SS_SLP_RET_N;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Turn on L1, L2, ETB and JU memories 1 at a time */
		val = readl(qproc->reg_base + QDSP6SS_MEM_PWR_CTL);
		for (i = 19; i >= 0; i--) {
			val |= BIT(i);
			writel(val, qproc->reg_base +
						QDSP6SS_MEM_PWR_CTL);
			/*
			 * Read back value to ensure the write is done then
			 * wait for 1us for both memory peripheral and data
			 * array to turn on.
			 */
			val |= readl(qproc->reg_base + QDSP6SS_MEM_PWR_CTL);
			udelay(1);
		}
		/* Remove word line clamp */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val &= ~QDSP6v56_CLAMP_WL;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	} else {
		/* Assert resets, stop core */
		val = readl(qproc->reg_base + QDSP6SS_RESET_REG);
		val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
		writel(val, qproc->reg_base + QDSP6SS_RESET_REG);

		/* Enable power block headswitch and wait for it to stabilize */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= QDSS_BHS_ON | QDSS_LDO_BYP;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		udelay(1);
		/*
		 * Turn on memories. L2 banks should be done individually
		 * to minimize inrush current.
		 */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_SLP_RET_N | Q6SS_L2TAG_SLP_NRET_N |
			Q6SS_ETB_SLP_NRET_N | Q6SS_L2DATA_STBY_N;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_2;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_1;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_0;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	}
	/* Remove IO clamp */
	val &= ~Q6SS_CLAMP_IO;
	writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

	/* Bring core out of reset */
	val = readl(qproc->reg_base + QDSP6SS_RESET_REG);
	val &= ~Q6SS_CORE_ARES;
	writel(val, qproc->reg_base + QDSP6SS_RESET_REG);

	/* Turn on core clock */
	val = readl(qproc->reg_base + QDSP6SS_GFMUX_CTL_REG);
	val |= Q6SS_CLK_ENABLE;
	writel(val, qproc->reg_base + QDSP6SS_GFMUX_CTL_REG);

	/* Start core execution */
	val = readl(qproc->reg_base + QDSP6SS_RESET_REG);
	val &= ~Q6SS_STOP_CORE;
	writel(val, qproc->reg_base + QDSP6SS_RESET_REG);

pbl_wait:
	/* Wait for PBL status */
	ret = q6v5_rmb_pbl_wait(qproc, 1000);
	if (ret == -ETIMEDOUT) {
		dev_err(qproc->dev, "PBL boot timed out\n");
	} else if (ret != RMB_PBL_SUCCESS) {
		dev_err(qproc->dev, "PBL returned unexpected status %d\n", ret);
		ret = -EINVAL;
	} else {
		ret = 0;
	}

	return ret;
}