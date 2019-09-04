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
struct msdc_host {int timeout_ns; int timeout_clks; unsigned long sclk; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_MSG (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  OPS ; 
 scalar_t__ SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_DTOC ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msdc_set_timeout(struct msdc_host *host, u32 ns, u32 clks)
{
	u32 timeout, clk_ns;

	host->timeout_ns   = ns;
	host->timeout_clks = clks;

	clk_ns  = 1000000000UL / host->sclk;
	timeout = ns / clk_ns + clks;
	timeout = timeout >> 16; /* in 65536 sclk cycle unit */
	timeout = timeout > 1 ? timeout - 1 : 0;
	timeout = timeout > 255 ? 255 : timeout;

	sdr_set_field(host->base + SDC_CFG, SDC_CFG_DTOC, timeout);

	N_MSG(OPS, "Set read data timeout: %dns %dclks -> %d x 65536 cycles",
	      ns, clks, timeout + 1);
}