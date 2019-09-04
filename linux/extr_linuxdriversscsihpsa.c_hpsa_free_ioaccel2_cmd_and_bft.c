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
struct ctlr_info {int nr_cmds; int /*<<< orphan*/ * ioaccel2_blockFetchTable; scalar_t__ ioaccel2_cmd_pool_dhandle; int /*<<< orphan*/ * ioaccel2_cmd_pool; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsa_free_ioaccel2_sg_chain_blocks (struct ctlr_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void hpsa_free_ioaccel2_cmd_and_bft(struct ctlr_info *h)
{
	hpsa_free_ioaccel2_sg_chain_blocks(h);

	if (h->ioaccel2_cmd_pool) {
		pci_free_consistent(h->pdev,
			h->nr_cmds * sizeof(*h->ioaccel2_cmd_pool),
			h->ioaccel2_cmd_pool,
			h->ioaccel2_cmd_pool_dhandle);
		h->ioaccel2_cmd_pool = NULL;
		h->ioaccel2_cmd_pool_dhandle = 0;
	}
	kfree(h->ioaccel2_blockFetchTable);
	h->ioaccel2_blockFetchTable = NULL;
}