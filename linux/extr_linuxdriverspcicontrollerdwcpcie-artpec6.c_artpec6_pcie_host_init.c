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
struct dw_pcie {int dummy; } ;
struct artpec6_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  artpec6_pcie_assert_core_reset (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_deassert_core_reset (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_enable_interrupts (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_establish_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_init_phy (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_set_nfts (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_wait_for_phy (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_wait_for_link (struct dw_pcie*) ; 
 struct artpec6_pcie* to_artpec6_pcie (struct dw_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

__attribute__((used)) static int artpec6_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);

	artpec6_pcie_assert_core_reset(artpec6_pcie);
	artpec6_pcie_init_phy(artpec6_pcie);
	artpec6_pcie_deassert_core_reset(artpec6_pcie);
	artpec6_pcie_wait_for_phy(artpec6_pcie);
	artpec6_pcie_set_nfts(artpec6_pcie);
	dw_pcie_setup_rc(pp);
	artpec6_pcie_establish_link(pci);
	dw_pcie_wait_for_link(pci);
	artpec6_pcie_enable_interrupts(artpec6_pcie);

	return 0;
}