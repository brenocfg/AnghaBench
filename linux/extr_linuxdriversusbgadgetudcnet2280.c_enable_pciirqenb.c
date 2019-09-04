#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net2280_ep {size_t num; TYPE_2__* dev; } ;
struct TYPE_4__ {int quirks; TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pciirqenb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int PLX_LEGACY ; 
 size_t* ep_bit ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void enable_pciirqenb(struct net2280_ep *ep)
{
	u32 tmp = readl(&ep->dev->regs->pciirqenb0);

	if (ep->dev->quirks & PLX_LEGACY)
		tmp |= BIT(ep->num);
	else
		tmp |= BIT(ep_bit[ep->num]);
	writel(tmp, &ep->dev->regs->pciirqenb0);

	return;
}