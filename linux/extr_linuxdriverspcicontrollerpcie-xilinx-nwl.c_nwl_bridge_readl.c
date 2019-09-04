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
typedef  scalar_t__ u32 ;
struct nwl_pcie {scalar_t__ breg_base; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static inline u32 nwl_bridge_readl(struct nwl_pcie *pcie, u32 off)
{
	return readl(pcie->breg_base + off);
}