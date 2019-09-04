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
typedef  size_t u32 ;
struct TYPE_3__ {scalar_t__ version; } ;
struct brcmf_pciedev_info {TYPE_2__* pdev; TYPE_1__ shared; } ;
struct brcmf_pcie_ringbuf {int /*<<< orphan*/  commonring; struct brcmf_pciedev_info* devinfo; int /*<<< orphan*/  dma_handle; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BRCMF_PCIE_SHARED_VERSION_7 ; 
 size_t BRCMF_RING_LEN_ITEMS_OFFSET ; 
 size_t BRCMF_RING_MAX_ITEM_OFFSET ; 
 size_t BRCMF_RING_MEM_BASE_ADDR_OFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcmf_commonring_config (int /*<<< orphan*/ *,size_t const,size_t const,void*) ; 
 int /*<<< orphan*/  brcmf_commonring_register_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_pcie_ringbuf*) ; 
 void* brcmf_pcie_init_dmabuffer_for_device (struct brcmf_pciedev_info*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_ring_bell ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_update_rptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_update_wptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_write_rptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_write_wptr ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm16 (struct brcmf_pciedev_info*,size_t,size_t const) ; 
 size_t* brcmf_ring_itemsize ; 
 size_t* brcmf_ring_itemsize_pre_v7 ; 
 size_t const* brcmf_ring_max_item ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 
 struct brcmf_pcie_ringbuf* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct brcmf_pcie_ringbuf *
brcmf_pcie_alloc_dma_and_ring(struct brcmf_pciedev_info *devinfo, u32 ring_id,
			      u32 tcm_ring_phys_addr)
{
	void *dma_buf;
	dma_addr_t dma_handle;
	struct brcmf_pcie_ringbuf *ring;
	u32 size;
	u32 addr;
	const u32 *ring_itemsize_array;

	if (devinfo->shared.version < BRCMF_PCIE_SHARED_VERSION_7)
		ring_itemsize_array = brcmf_ring_itemsize_pre_v7;
	else
		ring_itemsize_array = brcmf_ring_itemsize;

	size = brcmf_ring_max_item[ring_id] * ring_itemsize_array[ring_id];
	dma_buf = brcmf_pcie_init_dmabuffer_for_device(devinfo, size,
			tcm_ring_phys_addr + BRCMF_RING_MEM_BASE_ADDR_OFFSET,
			&dma_handle);
	if (!dma_buf)
		return NULL;

	addr = tcm_ring_phys_addr + BRCMF_RING_MAX_ITEM_OFFSET;
	brcmf_pcie_write_tcm16(devinfo, addr, brcmf_ring_max_item[ring_id]);
	addr = tcm_ring_phys_addr + BRCMF_RING_LEN_ITEMS_OFFSET;
	brcmf_pcie_write_tcm16(devinfo, addr, ring_itemsize_array[ring_id]);

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring) {
		dma_free_coherent(&devinfo->pdev->dev, size, dma_buf,
				  dma_handle);
		return NULL;
	}
	brcmf_commonring_config(&ring->commonring, brcmf_ring_max_item[ring_id],
				ring_itemsize_array[ring_id], dma_buf);
	ring->dma_handle = dma_handle;
	ring->devinfo = devinfo;
	brcmf_commonring_register_cb(&ring->commonring,
				     brcmf_pcie_ring_mb_ring_bell,
				     brcmf_pcie_ring_mb_update_rptr,
				     brcmf_pcie_ring_mb_update_wptr,
				     brcmf_pcie_ring_mb_write_rptr,
				     brcmf_pcie_ring_mb_write_wptr, ring);

	return (ring);
}