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
struct whc {int n_devices; scalar_t__ workqueue; scalar_t__ base_phys; scalar_t__ base; TYPE_1__* umc; int /*<<< orphan*/  qset_pool; int /*<<< orphan*/  gen_cmd_buf_dma; scalar_t__ gen_cmd_buf; int /*<<< orphan*/  dn_buf_dma; scalar_t__ dn_buf; int /*<<< orphan*/  di_buf_dma; scalar_t__ di_buf; } ;
struct dn_buf_entry {int dummy; } ;
struct di_buf_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WHC_GEN_CMD_DATA_LEN ; 
 int WHC_N_DN_ENTRIES ; 
 int /*<<< orphan*/  asl_clean_up (struct whc*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pzl_clean_up (struct whc*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 

void whc_clean_up(struct whc *whc)
{
	resource_size_t len;

	if (whc->di_buf)
		dma_free_coherent(&whc->umc->dev, sizeof(struct di_buf_entry) * whc->n_devices,
				  whc->di_buf, whc->di_buf_dma);
	if (whc->dn_buf)
		dma_free_coherent(&whc->umc->dev, sizeof(struct dn_buf_entry) * WHC_N_DN_ENTRIES,
				  whc->dn_buf, whc->dn_buf_dma);
	if (whc->gen_cmd_buf)
		dma_free_coherent(&whc->umc->dev, WHC_GEN_CMD_DATA_LEN,
				  whc->gen_cmd_buf, whc->gen_cmd_buf_dma);

	pzl_clean_up(whc);
	asl_clean_up(whc);

	dma_pool_destroy(whc->qset_pool);

	len   = resource_size(&whc->umc->resource);
	if (whc->base)
		iounmap(whc->base);
	if (whc->base_phys)
		release_mem_region(whc->base_phys, len);

	if (whc->workqueue)
		destroy_workqueue(whc->workqueue);
}