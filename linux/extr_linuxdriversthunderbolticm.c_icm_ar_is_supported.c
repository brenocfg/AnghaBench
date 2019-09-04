#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb {TYPE_1__* nhi; } ;
struct pci_dev {int dummy; } ;
struct icm {int vnd_cap; struct pci_dev* upstream_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_VNDR ; 
 struct pci_dev* get_upstream_port (int /*<<< orphan*/ ) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct icm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  x86_apple_machine ; 

__attribute__((used)) static bool icm_ar_is_supported(struct tb *tb)
{
	struct pci_dev *upstream_port;
	struct icm *icm = tb_priv(tb);

	/*
	 * Starting from Alpine Ridge we can use ICM on Apple machines
	 * as well. We just need to reset and re-enable it first.
	 */
	if (!x86_apple_machine)
		return true;

	/*
	 * Find the upstream PCIe port in case we need to do reset
	 * through its vendor specific registers.
	 */
	upstream_port = get_upstream_port(tb->nhi->pdev);
	if (upstream_port) {
		int cap;

		cap = pci_find_ext_capability(upstream_port,
					      PCI_EXT_CAP_ID_VNDR);
		if (cap > 0) {
			icm->upstream_port = upstream_port;
			icm->vnd_cap = cap;

			return true;
		}
	}

	return false;
}