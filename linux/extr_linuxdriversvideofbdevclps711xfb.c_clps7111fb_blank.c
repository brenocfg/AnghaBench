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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCON1 ; 
 int SYSCON1_LCDEN ; 
 int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clps7111fb_blank(int blank, struct fb_info *info)
{
	/* Enable/Disable LCD controller. */
	if (blank)
		clps_writel(clps_readl(SYSCON1) & ~SYSCON1_LCDEN, SYSCON1);
	else
		clps_writel(clps_readl(SYSCON1) | SYSCON1_LCDEN, SYSCON1);

	return 0;
}