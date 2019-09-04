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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {int dummy; } ;
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 int dw_pcie_read (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  histb_pcie_dbi_r_mode (struct pcie_port*,int) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

__attribute__((used)) static int histb_pcie_rd_own_conf(struct pcie_port *pp, int where,
				  int size, u32 *val)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	int ret;

	histb_pcie_dbi_r_mode(pp, true);
	ret = dw_pcie_read(pci->dbi_base + where, size, val);
	histb_pcie_dbi_r_mode(pp, false);

	return ret;
}