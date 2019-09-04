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
struct pcie_port {int dummy; } ;
struct ls_pcie {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_dis (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_en (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int /*<<< orphan*/  ls_pcie_clear_multifunction (struct ls_pcie*) ; 
 int /*<<< orphan*/  ls_pcie_disable_outbound_atus (struct ls_pcie*) ; 
 int /*<<< orphan*/  ls_pcie_drop_msg_tlp (struct ls_pcie*) ; 
 int /*<<< orphan*/  ls_pcie_fix_error_response (struct ls_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct ls_pcie* to_ls_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ls_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct ls_pcie *pcie = to_ls_pcie(pci);

	/*
	 * Disable outbound windows configured by the bootloader to avoid
	 * one transaction hitting multiple outbound windows.
	 * dw_pcie_setup_rc() will reconfigure the outbound windows.
	 */
	ls_pcie_disable_outbound_atus(pcie);
	ls_pcie_fix_error_response(pcie);

	dw_pcie_dbi_ro_wr_en(pci);
	ls_pcie_clear_multifunction(pcie);
	dw_pcie_dbi_ro_wr_dis(pci);

	ls_pcie_drop_msg_tlp(pcie);

	dw_pcie_setup_rc(pp);

	return 0;
}