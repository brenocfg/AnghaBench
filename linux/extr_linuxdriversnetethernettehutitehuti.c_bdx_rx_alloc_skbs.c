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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int pktsz; int va; int wptr; int memsz; int /*<<< orphan*/  reg_WPTR; } ;
struct rxf_fifo {TYPE_1__ m; } ;
struct rxf_desc {int va_lo; void* len; void* pa_hi; void* pa_lo; void* info; } ;
struct rxdb {int dummy; } ;
struct rx_map {int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct bdx_priv {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; struct rxdb* rxdb; } ;

/* Variables and functions */
 void* CPU_CHIP_SWAP32 (int) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  ENTER ; 
 int H32_64 (int /*<<< orphan*/ ) ; 
 int L32_64 (int /*<<< orphan*/ ) ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RET () ; 
 int TXF_WPTR_WR_PTR ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int /*<<< orphan*/ ,int) ; 
 struct rx_map* bdx_rxdb_addr_elem (struct rxdb*,int) ; 
 int bdx_rxdb_alloc_elem (struct rxdb*) ; 
 int bdx_rxdb_available (struct rxdb*) ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rxfd (struct rxf_desc*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bdx_rx_alloc_skbs(struct bdx_priv *priv, struct rxf_fifo *f)
{
	struct sk_buff *skb;
	struct rxf_desc *rxfd;
	struct rx_map *dm;
	int dno, delta, idx;
	struct rxdb *db = priv->rxdb;

	ENTER;
	dno = bdx_rxdb_available(db) - 1;
	while (dno > 0) {
		skb = netdev_alloc_skb(priv->ndev, f->m.pktsz + NET_IP_ALIGN);
		if (!skb)
			break;

		skb_reserve(skb, NET_IP_ALIGN);

		idx = bdx_rxdb_alloc_elem(db);
		dm = bdx_rxdb_addr_elem(db, idx);
		dm->dma = pci_map_single(priv->pdev,
					 skb->data, f->m.pktsz,
					 PCI_DMA_FROMDEVICE);
		dm->skb = skb;
		rxfd = (struct rxf_desc *)(f->m.va + f->m.wptr);
		rxfd->info = CPU_CHIP_SWAP32(0x10003);	/* INFO=1 BC=3 */
		rxfd->va_lo = idx;
		rxfd->pa_lo = CPU_CHIP_SWAP32(L32_64(dm->dma));
		rxfd->pa_hi = CPU_CHIP_SWAP32(H32_64(dm->dma));
		rxfd->len = CPU_CHIP_SWAP32(f->m.pktsz);
		print_rxfd(rxfd);

		f->m.wptr += sizeof(struct rxf_desc);
		delta = f->m.wptr - f->m.memsz;
		if (unlikely(delta >= 0)) {
			f->m.wptr = delta;
			if (delta > 0) {
				memcpy(f->m.va, f->m.va + f->m.memsz, delta);
				DBG("wrapped descriptor\n");
			}
		}
		dno--;
	}
	/*TBD: to do - delayed rxf wptr like in txd */
	WRITE_REG(priv, f->m.reg_WPTR, f->m.wptr & TXF_WPTR_WR_PTR);
	RET();
}