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
struct sk_buff {int dummy; } ;
struct cas_tx_desc {int /*<<< orphan*/  control; int /*<<< orphan*/  buffer; } ;
struct cas {TYPE_2__** tx_tiny_use; int /*<<< orphan*/  pdev; struct sk_buff*** tx_skbs; struct cas_tx_desc** init_txds; } ;
struct TYPE_4__ {scalar_t__ used; } ;
struct TYPE_3__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TX_DESC_BUFLEN ; 
 int TX_DESC_RINGN_SIZE (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void cas_clean_txd(struct cas *cp, int ring)
{
	struct cas_tx_desc *txd = cp->init_txds[ring];
	struct sk_buff *skb, **skbs = cp->tx_skbs[ring];
	u64 daddr, dlen;
	int i, size;

	size = TX_DESC_RINGN_SIZE(ring);
	for (i = 0; i < size; i++) {
		int frag;

		if (skbs[i] == NULL)
			continue;

		skb = skbs[i];
		skbs[i] = NULL;

		for (frag = 0; frag <= skb_shinfo(skb)->nr_frags;  frag++) {
			int ent = i & (size - 1);

			/* first buffer is never a tiny buffer and so
			 * needs to be unmapped.
			 */
			daddr = le64_to_cpu(txd[ent].buffer);
			dlen  =  CAS_VAL(TX_DESC_BUFLEN,
					 le64_to_cpu(txd[ent].control));
			pci_unmap_page(cp->pdev, daddr, dlen,
				       PCI_DMA_TODEVICE);

			if (frag != skb_shinfo(skb)->nr_frags) {
				i++;

				/* next buffer might by a tiny buffer.
				 * skip past it.
				 */
				ent = i & (size - 1);
				if (cp->tx_tiny_use[ring][ent].used)
					i++;
			}
		}
		dev_kfree_skb_any(skb);
	}

	/* zero out tiny buf usage */
	memset(cp->tx_tiny_use[ring], 0, size*sizeof(*cp->tx_tiny_use[ring]));
}