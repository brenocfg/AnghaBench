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
struct dw_pcie_ep {int dummy; } ;
struct dw_pcie {int dummy; } ;
struct artpec6_pcie {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int BAR_5 ; 
 int /*<<< orphan*/  artpec6_pcie_assert_core_reset (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_deassert_core_reset (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_init_phy (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_set_nfts (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_wait_for_phy (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_ep_reset_bar (struct dw_pcie*,int) ; 
 struct artpec6_pcie* to_artpec6_pcie (struct dw_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static void artpec6_pcie_ep_init(struct dw_pcie_ep *ep)
{
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	enum pci_barno bar;

	artpec6_pcie_assert_core_reset(artpec6_pcie);
	artpec6_pcie_init_phy(artpec6_pcie);
	artpec6_pcie_deassert_core_reset(artpec6_pcie);
	artpec6_pcie_wait_for_phy(artpec6_pcie);
	artpec6_pcie_set_nfts(artpec6_pcie);

	for (bar = BAR_0; bar <= BAR_5; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
}