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
struct ctlr_info {int max_cmd_sg_entries; int /*<<< orphan*/  pdev; } ;
struct SGDescriptor {int /*<<< orphan*/  Len; int /*<<< orphan*/  Addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  SGTotal; } ;
struct CommandList {struct SGDescriptor* SG; TYPE_1__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_unmap_sg_chain_block(struct ctlr_info *h,
	struct CommandList *c)
{
	struct SGDescriptor *chain_sg;

	if (le16_to_cpu(c->Header.SGTotal) <= h->max_cmd_sg_entries)
		return;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	pci_unmap_single(h->pdev, le64_to_cpu(chain_sg->Addr),
			le32_to_cpu(chain_sg->Len), PCI_DMA_TODEVICE);
}