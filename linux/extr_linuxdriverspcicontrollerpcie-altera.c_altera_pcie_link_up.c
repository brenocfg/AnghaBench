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
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int LTSSM_L0 ; 
 int /*<<< orphan*/  RP_LTSSM ; 
 int RP_LTSSM_MASK ; 
 int cra_readl (struct altera_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool altera_pcie_link_up(struct altera_pcie *pcie)
{
	return !!((cra_readl(pcie, RP_LTSSM) & RP_LTSSM_MASK) == LTSSM_L0);
}