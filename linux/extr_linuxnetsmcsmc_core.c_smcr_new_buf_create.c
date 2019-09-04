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
struct smc_link_group {struct smc_link* lnk; } ;
struct smc_link {int /*<<< orphan*/  roce_pd; int /*<<< orphan*/  smcibdev; } ;
struct smc_buf_desc {int len; void* cpu_addr; TYPE_1__* sgt; int /*<<< orphan*/  pages; int /*<<< orphan*/  order; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 struct smc_buf_desc* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 size_t SMC_SINGLE_LINK ; 
 int __GFP_COMP ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct smc_buf_desc*) ; 
 struct smc_buf_desc* kzalloc (int,int) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int sg_alloc_table (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  smc_buf_free (struct smc_link_group*,int,struct smc_buf_desc*) ; 
 int smc_ib_buf_map_sg (int /*<<< orphan*/ ,struct smc_buf_desc*,int /*<<< orphan*/ ) ; 
 int smc_ib_get_memory_region (int /*<<< orphan*/ ,int,struct smc_buf_desc*) ; 

__attribute__((used)) static struct smc_buf_desc *smcr_new_buf_create(struct smc_link_group *lgr,
						bool is_rmb, int bufsize)
{
	struct smc_buf_desc *buf_desc;
	struct smc_link *lnk;
	int rc;

	/* try to alloc a new buffer */
	buf_desc = kzalloc(sizeof(*buf_desc), GFP_KERNEL);
	if (!buf_desc)
		return ERR_PTR(-ENOMEM);

	buf_desc->order = get_order(bufsize);
	buf_desc->pages = alloc_pages(GFP_KERNEL | __GFP_NOWARN |
				      __GFP_NOMEMALLOC | __GFP_COMP |
				      __GFP_NORETRY | __GFP_ZERO,
				      buf_desc->order);
	if (!buf_desc->pages) {
		kfree(buf_desc);
		return ERR_PTR(-EAGAIN);
	}
	buf_desc->cpu_addr = (void *)page_address(buf_desc->pages);

	/* build the sg table from the pages */
	lnk = &lgr->lnk[SMC_SINGLE_LINK];
	rc = sg_alloc_table(&buf_desc->sgt[SMC_SINGLE_LINK], 1,
			    GFP_KERNEL);
	if (rc) {
		smc_buf_free(lgr, is_rmb, buf_desc);
		return ERR_PTR(rc);
	}
	sg_set_buf(buf_desc->sgt[SMC_SINGLE_LINK].sgl,
		   buf_desc->cpu_addr, bufsize);

	/* map sg table to DMA address */
	rc = smc_ib_buf_map_sg(lnk->smcibdev, buf_desc,
			       is_rmb ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	/* SMC protocol depends on mapping to one DMA address only */
	if (rc != 1)  {
		smc_buf_free(lgr, is_rmb, buf_desc);
		return ERR_PTR(-EAGAIN);
	}

	/* create a new memory region for the RMB */
	if (is_rmb) {
		rc = smc_ib_get_memory_region(lnk->roce_pd,
					      IB_ACCESS_REMOTE_WRITE |
					      IB_ACCESS_LOCAL_WRITE,
					      buf_desc);
		if (rc) {
			smc_buf_free(lgr, is_rmb, buf_desc);
			return ERR_PTR(rc);
		}
	}

	buf_desc->len = bufsize;
	return buf_desc;
}