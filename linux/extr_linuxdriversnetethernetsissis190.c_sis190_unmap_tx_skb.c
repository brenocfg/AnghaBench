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
struct sk_buff {unsigned int len; } ;
struct pci_dev {int dummy; } ;
struct TxDesc {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned int ETH_ZLEN ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct TxDesc*,int,int) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis190_unmap_tx_skb(struct pci_dev *pdev, struct sk_buff *skb,
				struct TxDesc *desc)
{
	unsigned int len;

	len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;

	pci_unmap_single(pdev, le32_to_cpu(desc->addr), len, PCI_DMA_TODEVICE);

	memset(desc, 0x00, sizeof(*desc));
}