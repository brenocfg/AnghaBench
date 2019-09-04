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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct rocker_port {struct rocker* rocker; } ;
struct rocker_desc_info {scalar_t__ tlv_size; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EIO ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  ROCKER_TLV_RX_FRAG_ADDR ; 
 int /*<<< orphan*/  ROCKER_TLV_RX_FRAG_MAX_LEN ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ rocker_tlv_put_u64 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_dma_rx_ring_skb_map(const struct rocker_port *rocker_port,
				      struct rocker_desc_info *desc_info,
				      struct sk_buff *skb, size_t buf_len)
{
	const struct rocker *rocker = rocker_port->rocker;
	struct pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;

	dma_handle = pci_map_single(pdev, skb->data, buf_len,
				    PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(pdev, dma_handle))
		return -EIO;
	if (rocker_tlv_put_u64(desc_info, ROCKER_TLV_RX_FRAG_ADDR, dma_handle))
		goto tlv_put_failure;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_RX_FRAG_MAX_LEN, buf_len))
		goto tlv_put_failure;
	return 0;

tlv_put_failure:
	pci_unmap_single(pdev, dma_handle, buf_len, PCI_DMA_FROMDEVICE);
	desc_info->tlv_size = 0;
	return -EMSGSIZE;
}