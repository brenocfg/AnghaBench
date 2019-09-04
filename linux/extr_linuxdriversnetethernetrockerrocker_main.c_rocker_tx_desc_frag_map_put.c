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
struct rocker_tlv {int dummy; } ;
struct rocker_port {int /*<<< orphan*/  dev; struct rocker* rocker; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ROCKER_TLV_TX_FRAG ; 
 int /*<<< orphan*/  ROCKER_TLV_TX_FRAG_ATTR_ADDR ; 
 int /*<<< orphan*/  ROCKER_TLV_TX_FRAG_ATTR_LEN ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_tlv_nest_cancel (struct rocker_desc_info*,struct rocker_tlv*) ; 
 int /*<<< orphan*/  rocker_tlv_nest_end (struct rocker_desc_info*,struct rocker_tlv*) ; 
 struct rocker_tlv* rocker_tlv_nest_start (struct rocker_desc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ rocker_tlv_put_u64 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_tx_desc_frag_map_put(const struct rocker_port *rocker_port,
				       struct rocker_desc_info *desc_info,
				       char *buf, size_t buf_len)
{
	const struct rocker *rocker = rocker_port->rocker;
	struct pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;
	struct rocker_tlv *frag;

	dma_handle = pci_map_single(pdev, buf, buf_len, DMA_TO_DEVICE);
	if (unlikely(pci_dma_mapping_error(pdev, dma_handle))) {
		if (net_ratelimit())
			netdev_err(rocker_port->dev, "failed to dma map tx frag\n");
		return -EIO;
	}
	frag = rocker_tlv_nest_start(desc_info, ROCKER_TLV_TX_FRAG);
	if (!frag)
		goto unmap_frag;
	if (rocker_tlv_put_u64(desc_info, ROCKER_TLV_TX_FRAG_ATTR_ADDR,
			       dma_handle))
		goto nest_cancel;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_TX_FRAG_ATTR_LEN,
			       buf_len))
		goto nest_cancel;
	rocker_tlv_nest_end(desc_info, frag);
	return 0;

nest_cancel:
	rocker_tlv_nest_cancel(desc_info, frag);
unmap_frag:
	pci_unmap_single(pdev, dma_handle, buf_len, DMA_TO_DEVICE);
	return -EMSGSIZE;
}