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
struct ath5k_hw {int desc_len; int desc_daddr; int txbuf_len; struct ath5k_desc* desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  bcbuf; int /*<<< orphan*/  txbuf; int /*<<< orphan*/  rxbuf; struct ath5k_buf* bufptr; } ;
struct ath5k_desc {int dummy; } ;
struct ath5k_buf {int daddr; int /*<<< orphan*/  list; struct ath5k_desc* desc; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,struct ath5k_desc*,int,unsigned long long) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANY ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int ATH_BCBUF ; 
 int ATH_RXBUF ; 
 int ATH_TXBUF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ath5k_desc* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct ath5k_desc*,int) ; 
 struct ath5k_buf* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath5k_desc_alloc(struct ath5k_hw *ah)
{
	struct ath5k_desc *ds;
	struct ath5k_buf *bf;
	dma_addr_t da;
	unsigned int i;
	int ret;

	/* allocate descriptors */
	ah->desc_len = sizeof(struct ath5k_desc) *
			(ATH_TXBUF + ATH_RXBUF + ATH_BCBUF + 1);

	ah->desc = dma_alloc_coherent(ah->dev, ah->desc_len,
				&ah->desc_daddr, GFP_KERNEL);
	if (ah->desc == NULL) {
		ATH5K_ERR(ah, "can't allocate descriptors\n");
		ret = -ENOMEM;
		goto err;
	}
	ds = ah->desc;
	da = ah->desc_daddr;
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "DMA map: %p (%zu) -> %llx\n",
		ds, ah->desc_len, (unsigned long long)ah->desc_daddr);

	bf = kcalloc(1 + ATH_TXBUF + ATH_RXBUF + ATH_BCBUF,
			sizeof(struct ath5k_buf), GFP_KERNEL);
	if (bf == NULL) {
		ATH5K_ERR(ah, "can't allocate bufptr\n");
		ret = -ENOMEM;
		goto err_free;
	}
	ah->bufptr = bf;

	INIT_LIST_HEAD(&ah->rxbuf);
	for (i = 0; i < ATH_RXBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->rxbuf);
	}

	INIT_LIST_HEAD(&ah->txbuf);
	ah->txbuf_len = ATH_TXBUF;
	for (i = 0; i < ATH_TXBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->txbuf);
	}

	/* beacon buffers */
	INIT_LIST_HEAD(&ah->bcbuf);
	for (i = 0; i < ATH_BCBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->bcbuf);
	}

	return 0;
err_free:
	dma_free_coherent(ah->dev, ah->desc_len, ah->desc, ah->desc_daddr);
err:
	ah->desc = NULL;
	return ret;
}