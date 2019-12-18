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
struct smc_link {void* wr_tx_bufs; void* wr_rx_bufs; void* wr_tx_ibs; void* wr_rx_ibs; void* wr_tx_rdmas; void* wr_tx_rdma_sges; void* wr_tx_sges; void* wr_rx_sges; void* wr_tx_mask; void* wr_tx_pends; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMC_WR_BUF_CNT ; 
 int SMC_WR_BUF_SIZE ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

int smc_wr_alloc_link_mem(struct smc_link *link)
{
	/* allocate link related memory */
	link->wr_tx_bufs = kcalloc(SMC_WR_BUF_CNT, SMC_WR_BUF_SIZE, GFP_KERNEL);
	if (!link->wr_tx_bufs)
		goto no_mem;
	link->wr_rx_bufs = kcalloc(SMC_WR_BUF_CNT * 3, SMC_WR_BUF_SIZE,
				   GFP_KERNEL);
	if (!link->wr_rx_bufs)
		goto no_mem_wr_tx_bufs;
	link->wr_tx_ibs = kcalloc(SMC_WR_BUF_CNT, sizeof(link->wr_tx_ibs[0]),
				  GFP_KERNEL);
	if (!link->wr_tx_ibs)
		goto no_mem_wr_rx_bufs;
	link->wr_rx_ibs = kcalloc(SMC_WR_BUF_CNT * 3,
				  sizeof(link->wr_rx_ibs[0]),
				  GFP_KERNEL);
	if (!link->wr_rx_ibs)
		goto no_mem_wr_tx_ibs;
	link->wr_tx_rdmas = kcalloc(SMC_WR_BUF_CNT,
				    sizeof(link->wr_tx_rdmas[0]),
				    GFP_KERNEL);
	if (!link->wr_tx_rdmas)
		goto no_mem_wr_rx_ibs;
	link->wr_tx_rdma_sges = kcalloc(SMC_WR_BUF_CNT,
					sizeof(link->wr_tx_rdma_sges[0]),
					GFP_KERNEL);
	if (!link->wr_tx_rdma_sges)
		goto no_mem_wr_tx_rdmas;
	link->wr_tx_sges = kcalloc(SMC_WR_BUF_CNT, sizeof(link->wr_tx_sges[0]),
				   GFP_KERNEL);
	if (!link->wr_tx_sges)
		goto no_mem_wr_tx_rdma_sges;
	link->wr_rx_sges = kcalloc(SMC_WR_BUF_CNT * 3,
				   sizeof(link->wr_rx_sges[0]),
				   GFP_KERNEL);
	if (!link->wr_rx_sges)
		goto no_mem_wr_tx_sges;
	link->wr_tx_mask = kcalloc(BITS_TO_LONGS(SMC_WR_BUF_CNT),
				   sizeof(*link->wr_tx_mask),
				   GFP_KERNEL);
	if (!link->wr_tx_mask)
		goto no_mem_wr_rx_sges;
	link->wr_tx_pends = kcalloc(SMC_WR_BUF_CNT,
				    sizeof(link->wr_tx_pends[0]),
				    GFP_KERNEL);
	if (!link->wr_tx_pends)
		goto no_mem_wr_tx_mask;
	return 0;

no_mem_wr_tx_mask:
	kfree(link->wr_tx_mask);
no_mem_wr_rx_sges:
	kfree(link->wr_rx_sges);
no_mem_wr_tx_sges:
	kfree(link->wr_tx_sges);
no_mem_wr_tx_rdma_sges:
	kfree(link->wr_tx_rdma_sges);
no_mem_wr_tx_rdmas:
	kfree(link->wr_tx_rdmas);
no_mem_wr_rx_ibs:
	kfree(link->wr_rx_ibs);
no_mem_wr_tx_ibs:
	kfree(link->wr_tx_ibs);
no_mem_wr_rx_bufs:
	kfree(link->wr_rx_bufs);
no_mem_wr_tx_bufs:
	kfree(link->wr_tx_bufs);
no_mem:
	return -ENOMEM;
}