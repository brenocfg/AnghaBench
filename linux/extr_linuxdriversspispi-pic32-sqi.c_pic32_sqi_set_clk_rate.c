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
struct pic32_sqi {scalar_t__ regs; int /*<<< orphan*/  base_clk; } ;

/* Variables and functions */
 int PESQI_CLKDIV ; 
 int PESQI_CLKDIV_SHIFT ; 
 scalar_t__ PESQI_CLK_CTRL_REG ; 
 int PESQI_CLK_STABLE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pic32_sqi_set_clk_rate(struct pic32_sqi *sqi, u32 sck)
{
	u32 val, div;

	/* div = base_clk / (2 * spi_clk) */
	div = clk_get_rate(sqi->base_clk) / (2 * sck);
	div &= PESQI_CLKDIV;

	val = readl(sqi->regs + PESQI_CLK_CTRL_REG);
	/* apply new divider */
	val &= ~(PESQI_CLK_STABLE | (PESQI_CLKDIV << PESQI_CLKDIV_SHIFT));
	val |= div << PESQI_CLKDIV_SHIFT;
	writel(val, sqi->regs + PESQI_CLK_CTRL_REG);

	/* wait for stability */
	return readl_poll_timeout(sqi->regs + PESQI_CLK_CTRL_REG, val,
				  val & PESQI_CLK_STABLE, 1, 5000);
}