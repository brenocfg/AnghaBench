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

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ IMX31_AUDMUX ; 
 scalar_t__ IMX_AUDMUX_V2_PDCR (unsigned int) ; 
 scalar_t__ IMX_AUDMUX_V2_PTCR (unsigned int) ; 
 scalar_t__ audmux_base ; 
 scalar_t__ audmux_clk ; 
 scalar_t__ audmux_type ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

int imx_audmux_v2_configure_port(unsigned int port, unsigned int ptcr,
		unsigned int pdcr)
{
	int ret;

	if (audmux_type != IMX31_AUDMUX)
		return -EINVAL;

	if (!audmux_base)
		return -ENOSYS;

	if (audmux_clk) {
		ret = clk_prepare_enable(audmux_clk);
		if (ret)
			return ret;
	}

	writel(ptcr, audmux_base + IMX_AUDMUX_V2_PTCR(port));
	writel(pdcr, audmux_base + IMX_AUDMUX_V2_PDCR(port));

	if (audmux_clk)
		clk_disable_unprepare(audmux_clk);

	return 0;
}