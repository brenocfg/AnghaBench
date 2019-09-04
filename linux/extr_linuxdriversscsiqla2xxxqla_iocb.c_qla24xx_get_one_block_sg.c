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
typedef  scalar_t__ uint32_t ;
struct scatterlist {int dummy; } ;
struct qla2_sgx {scalar_t__ num_bytes; scalar_t__ tot_bytes; scalar_t__ tot_partial; scalar_t__ dma_addr; scalar_t__ bytes_consumed; scalar_t__ dma_len; struct scatterlist* cur_sg; int /*<<< orphan*/  num_sg; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

int
qla24xx_get_one_block_sg(uint32_t blk_sz, struct qla2_sgx *sgx,
	uint32_t *partial)
{
	struct scatterlist *sg;
	uint32_t cumulative_partial, sg_len;
	dma_addr_t sg_dma_addr;

	if (sgx->num_bytes == sgx->tot_bytes)
		return 0;

	sg = sgx->cur_sg;
	cumulative_partial = sgx->tot_partial;

	sg_dma_addr = sg_dma_address(sg);
	sg_len = sg_dma_len(sg);

	sgx->dma_addr = sg_dma_addr + sgx->bytes_consumed;

	if ((cumulative_partial + (sg_len - sgx->bytes_consumed)) >= blk_sz) {
		sgx->dma_len = (blk_sz - cumulative_partial);
		sgx->tot_partial = 0;
		sgx->num_bytes += blk_sz;
		*partial = 0;
	} else {
		sgx->dma_len = sg_len - sgx->bytes_consumed;
		sgx->tot_partial += sgx->dma_len;
		*partial = 1;
	}

	sgx->bytes_consumed += sgx->dma_len;

	if (sg_len == sgx->bytes_consumed) {
		sg = sg_next(sg);
		sgx->num_sg++;
		sgx->cur_sg = sg;
		sgx->bytes_consumed = 0;
	}

	return 1;
}