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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int SGList; void* SGTotal; } ;
struct CommandList {TYPE_2__ Header; TYPE_1__* SG; } ;
struct TYPE_3__ {void* Ext; void* Len; int /*<<< orphan*/  Addr; } ;

/* Variables and functions */
 size_t HPSA_SG_LAST ; 
 int PCI_DMA_NONE ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,unsigned char*,size_t,int) ; 

__attribute__((used)) static int hpsa_map_one(struct pci_dev *pdev,
		struct CommandList *cp,
		unsigned char *buf,
		size_t buflen,
		int data_direction)
{
	u64 addr64;

	if (buflen == 0 || data_direction == PCI_DMA_NONE) {
		cp->Header.SGList = 0;
		cp->Header.SGTotal = cpu_to_le16(0);
		return 0;
	}

	addr64 = pci_map_single(pdev, buf, buflen, data_direction);
	if (dma_mapping_error(&pdev->dev, addr64)) {
		/* Prevent subsequent unmap of something never mapped */
		cp->Header.SGList = 0;
		cp->Header.SGTotal = cpu_to_le16(0);
		return -1;
	}
	cp->SG[0].Addr = cpu_to_le64(addr64);
	cp->SG[0].Len = cpu_to_le32(buflen);
	cp->SG[0].Ext = cpu_to_le32(HPSA_SG_LAST); /* we are not chaining */
	cp->Header.SGList = 1;   /* no. SGs contig in this cmd */
	cp->Header.SGTotal = cpu_to_le16(1); /* total sgs in cmd list */
	return 0;
}