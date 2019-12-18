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
struct smc_link_group {struct smc_link* lnk; } ;
struct smc_link {int /*<<< orphan*/  smcibdev; } ;
struct smc_buf_desc {int /*<<< orphan*/  order; scalar_t__ pages; int /*<<< orphan*/ * sgt; scalar_t__* mr_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  __free_pages (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smc_buf_desc*) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_ib_buf_unmap_sg (int /*<<< orphan*/ ,struct smc_buf_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_ib_put_memory_region (scalar_t__) ; 

__attribute__((used)) static void smcr_buf_free(struct smc_link_group *lgr, bool is_rmb,
			  struct smc_buf_desc *buf_desc)
{
	struct smc_link *lnk = &lgr->lnk[SMC_SINGLE_LINK];

	if (is_rmb) {
		if (buf_desc->mr_rx[SMC_SINGLE_LINK])
			smc_ib_put_memory_region(
					buf_desc->mr_rx[SMC_SINGLE_LINK]);
		smc_ib_buf_unmap_sg(lnk->smcibdev, buf_desc,
				    DMA_FROM_DEVICE);
	} else {
		smc_ib_buf_unmap_sg(lnk->smcibdev, buf_desc,
				    DMA_TO_DEVICE);
	}
	sg_free_table(&buf_desc->sgt[SMC_SINGLE_LINK]);
	if (buf_desc->pages)
		__free_pages(buf_desc->pages, buf_desc->order);
	kfree(buf_desc);
}