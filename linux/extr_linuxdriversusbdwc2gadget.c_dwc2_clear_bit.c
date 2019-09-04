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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int dwc2_readl (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int) ; 

__attribute__((used)) static inline void dwc2_clear_bit(struct dwc2_hsotg *hsotg, u32 offset, u32 val)
{
	dwc2_writel(hsotg, dwc2_readl(hsotg, offset) & ~val, offset);
}