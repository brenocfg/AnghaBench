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
struct cas {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ REG_MAC_ALIGN_ERR ; 
 scalar_t__ REG_MAC_ATTEMPTS_PEAK ; 
 scalar_t__ REG_MAC_COLL_EXCESS ; 
 scalar_t__ REG_MAC_COLL_FIRST ; 
 scalar_t__ REG_MAC_COLL_LATE ; 
 scalar_t__ REG_MAC_COLL_NORMAL ; 
 scalar_t__ REG_MAC_FCS_ERR ; 
 scalar_t__ REG_MAC_LEN_ERR ; 
 scalar_t__ REG_MAC_RECV_FRAME ; 
 scalar_t__ REG_MAC_RX_CODE_ERR ; 
 scalar_t__ REG_MAC_TIMER_DEFER ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cas_clear_mac_err(struct cas *cp)
{
	writel(0, cp->regs + REG_MAC_COLL_NORMAL);
	writel(0, cp->regs + REG_MAC_COLL_FIRST);
	writel(0, cp->regs + REG_MAC_COLL_EXCESS);
	writel(0, cp->regs + REG_MAC_COLL_LATE);
	writel(0, cp->regs + REG_MAC_TIMER_DEFER);
	writel(0, cp->regs + REG_MAC_ATTEMPTS_PEAK);
	writel(0, cp->regs + REG_MAC_RECV_FRAME);
	writel(0, cp->regs + REG_MAC_LEN_ERR);
	writel(0, cp->regs + REG_MAC_ALIGN_ERR);
	writel(0, cp->regs + REG_MAC_FCS_ERR);
	writel(0, cp->regs + REG_MAC_RX_CODE_ERR);
}