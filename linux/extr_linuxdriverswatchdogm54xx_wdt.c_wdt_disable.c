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
 int /*<<< orphan*/  MCF_GPT_GMS0 ; 
 unsigned int MCF_GPT_GMS_CE ; 
 unsigned int MCF_GPT_GMS_WDEN ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_disable(void)
{
	unsigned int gms0;

	/* disable watchdog */
	gms0 = __raw_readl(MCF_GPT_GMS0);
	gms0 &= ~(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE);
	__raw_writel(gms0, MCF_GPT_GMS0);
}