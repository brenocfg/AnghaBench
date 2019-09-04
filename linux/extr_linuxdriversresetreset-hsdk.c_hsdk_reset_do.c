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
struct hsdk_rst {scalar_t__ regs_rst; } ;

/* Variables and functions */
 scalar_t__ CGU_IP_SW_RESET ; 
 int CGU_IP_SW_RESET_DELAY ; 
 int CGU_IP_SW_RESET_DELAY_MASK ; 
 int CGU_IP_SW_RESET_DELAY_SHIFT ; 
 int CGU_IP_SW_RESET_RESET ; 
 int /*<<< orphan*/  SW_RESET_TIMEOUT ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hsdk_reset_do(struct hsdk_rst *rst)
{
	u32 reg;

	reg = readl(rst->regs_rst + CGU_IP_SW_RESET);
	reg &= ~CGU_IP_SW_RESET_DELAY_MASK;
	reg |= CGU_IP_SW_RESET_DELAY << CGU_IP_SW_RESET_DELAY_SHIFT;
	reg |= CGU_IP_SW_RESET_RESET;
	writel(reg, rst->regs_rst + CGU_IP_SW_RESET);

	/* wait till reset bit is back to 0 */
	return readl_poll_timeout_atomic(rst->regs_rst + CGU_IP_SW_RESET, reg,
		!(reg & CGU_IP_SW_RESET_RESET), 5, SW_RESET_TIMEOUT);
}