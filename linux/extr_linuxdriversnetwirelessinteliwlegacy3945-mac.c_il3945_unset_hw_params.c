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
struct TYPE_4__ {int /*<<< orphan*/  shared_phys; scalar_t__ shared_virt; } ;
struct il_priv {TYPE_2__ _3945; TYPE_1__* pci_dev; } ;
struct il3945_shared {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il3945_unset_hw_params(struct il_priv *il)
{
	if (il->_3945.shared_virt)
		dma_free_coherent(&il->pci_dev->dev,
				  sizeof(struct il3945_shared),
				  il->_3945.shared_virt, il->_3945.shared_phys);
}