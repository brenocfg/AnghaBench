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
struct mobiveil_pcie {int dummy; } ;

/* Variables and functions */
 int PAGE_LO_MASK ; 
 int PAGE_SEL_EN ; 
 int csr_readl (struct mobiveil_pcie*,int) ; 
 int /*<<< orphan*/  select_paged_register (struct mobiveil_pcie*,int) ; 

__attribute__((used)) static u32 read_paged_register(struct mobiveil_pcie *pcie, u32 offset)
{
	u32 off = (offset & PAGE_LO_MASK) | PAGE_SEL_EN;

	select_paged_register(pcie, offset);
	return csr_readl(pcie, off);
}