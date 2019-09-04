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
typedef  unsigned long u32 ;
struct ocotp_priv {scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DEF_RELAX ; 
 scalar_t__ IMX_OCOTP_ADDR_TIMING ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void imx_ocotp_set_imx6_timing(struct ocotp_priv *priv)
{
	unsigned long clk_rate = 0;
	unsigned long strobe_read, relax, strobe_prog;
	u32 timing = 0;

	/* 47.3.1.3.1
	 * Program HW_OCOTP_TIMING[STROBE_PROG] and HW_OCOTP_TIMING[RELAX]
	 * fields with timing values to match the current frequency of the
	 * ipg_clk. OTP writes will work at maximum bus frequencies as long
	 * as the HW_OCOTP_TIMING parameters are set correctly.
	 */
	clk_rate = clk_get_rate(priv->clk);

	relax = clk_rate / (1000000000 / DEF_RELAX) - 1;
	strobe_prog = clk_rate / (1000000000 / 10000) + 2 * (DEF_RELAX + 1) - 1;
	strobe_read = clk_rate / (1000000000 / 40) + 2 * (DEF_RELAX + 1) - 1;

	timing = strobe_prog & 0x00000FFF;
	timing |= (relax       << 12) & 0x0000F000;
	timing |= (strobe_read << 16) & 0x003F0000;

	writel(timing, priv->base + IMX_OCOTP_ADDR_TIMING);
}