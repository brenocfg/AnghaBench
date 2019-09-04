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
struct msdc_host {int hclk; int sclk; unsigned int mclk; int /*<<< orphan*/  timeout_clks; int /*<<< orphan*/  timeout_ns; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_MSG (char*,...) ; 
 scalar_t__ MSDC_CFG ; 
 int /*<<< orphan*/  MSDC_CFG_CKDIV ; 
 int /*<<< orphan*/  MSDC_CFG_CKMOD ; 
 int MSDC_CFG_CKSTB ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  msdc_irq_restore (int) ; 
 int /*<<< orphan*/  msdc_irq_save (int) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_set_timeout (struct msdc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msdc_set_mclk(struct msdc_host *host, int ddr, unsigned int hz)
{
	//struct msdc_hw *hw = host->hw;
	u32 mode;
	u32 flags;
	u32 div;
	u32 sclk;
	u32 hclk = host->hclk;
	//u8  clksrc = hw->clk_src;

	if (!hz) { // set mmc system clock to 0 ?
		//ERR_MSG("set mclk to 0!!!");
		msdc_reset_hw(host);
		return;
	}

	msdc_irq_save(flags);

	if (ddr) {
		mode = 0x2; /* ddr mode and use divisor */
		if (hz >= (hclk >> 2)) {
			div  = 1;         /* mean div = 1/4 */
			sclk = hclk >> 2; /* sclk = clk / 4 */
		} else {
			div  = (hclk + ((hz << 2) - 1)) / (hz << 2);
			sclk = (hclk >> 2) / div;
		}
	} else if (hz >= hclk) { /* bug fix */
		mode = 0x1; /* no divisor and divisor is ignored */
		div  = 0;
		sclk = hclk;
	} else {
		mode = 0x0; /* use divisor */
		if (hz >= (hclk >> 1)) {
			div  = 0;         /* mean div = 1/2 */
			sclk = hclk >> 1; /* sclk = clk / 2 */
		} else {
			div  = (hclk + ((hz << 2) - 1)) / (hz << 2);
			sclk = (hclk >> 2) / div;
		}
	}

	/* set clock mode and divisor */
	sdr_set_field(host->base + MSDC_CFG, MSDC_CFG_CKMOD, mode);
	sdr_set_field(host->base + MSDC_CFG, MSDC_CFG_CKDIV, div);

	/* wait clock stable */
	while (!(readl(host->base + MSDC_CFG) & MSDC_CFG_CKSTB))
		cpu_relax();

	host->sclk = sclk;
	host->mclk = hz;
	msdc_set_timeout(host, host->timeout_ns, host->timeout_clks); // need?

	INIT_MSG("================");
	INIT_MSG("!!! Set<%dKHz> Source<%dKHz> -> sclk<%dKHz>", hz / 1000, hclk / 1000, sclk / 1000);
	INIT_MSG("================");

	msdc_irq_restore(flags);
}