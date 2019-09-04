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
struct sdio_func {int /*<<< orphan*/  dev; int /*<<< orphan*/  cur_blksize; int /*<<< orphan*/  max_blksize; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  num; } ;
struct sdio_device_id {int dummy; } ;
struct ath6kl_sdio {int is_disabled; struct ath6kl_sdio* dma_buffer; struct ath6kl* ar; struct sdio_func* func; int /*<<< orphan*/ * bus_req; int /*<<< orphan*/  irq_wq; int /*<<< orphan*/  wr_async_work; int /*<<< orphan*/  wr_asyncq; int /*<<< orphan*/  bus_req_freeq; int /*<<< orphan*/  scat_req; int /*<<< orphan*/  dma_buffer_mutex; int /*<<< orphan*/  wr_async_lock; int /*<<< orphan*/  scat_lock; int /*<<< orphan*/  lock; struct sdio_device_id const* id; } ;
struct TYPE_2__ {int max_data_size; } ;
struct ath6kl {TYPE_1__ bmi; int /*<<< orphan*/ * hif_ops; struct ath6kl_sdio* hif_priv; int /*<<< orphan*/  hif_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  ATH6KL_HIF_TYPE_SDIO ; 
 int /*<<< orphan*/  ATH6KL_HTC_TYPE_MBOX ; 
 int BUS_REQUEST_MAX_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIF_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ath6kl* ath6kl_core_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_core_destroy (struct ath6kl*) ; 
 int ath6kl_core_init (struct ath6kl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,...) ; 
 int ath6kl_sdio_config (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_sdio_free_bus_req (struct ath6kl_sdio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_sdio_ops ; 
 int /*<<< orphan*/  ath6kl_sdio_set_mbox_info (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_sdio_write_async_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ath6kl_sdio*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct ath6kl_sdio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_sdio_probe(struct sdio_func *func,
			     const struct sdio_device_id *id)
{
	int ret;
	struct ath6kl_sdio *ar_sdio;
	struct ath6kl *ar;
	int count;

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "sdio new func %d vendor 0x%x device 0x%x block 0x%x/0x%x\n",
		   func->num, func->vendor, func->device,
		   func->max_blksize, func->cur_blksize);

	ar_sdio = kzalloc(sizeof(struct ath6kl_sdio), GFP_KERNEL);
	if (!ar_sdio)
		return -ENOMEM;

	ar_sdio->dma_buffer = kzalloc(HIF_DMA_BUFFER_SIZE, GFP_KERNEL);
	if (!ar_sdio->dma_buffer) {
		ret = -ENOMEM;
		goto err_hif;
	}

	ar_sdio->func = func;
	sdio_set_drvdata(func, ar_sdio);

	ar_sdio->id = id;
	ar_sdio->is_disabled = true;

	spin_lock_init(&ar_sdio->lock);
	spin_lock_init(&ar_sdio->scat_lock);
	spin_lock_init(&ar_sdio->wr_async_lock);
	mutex_init(&ar_sdio->dma_buffer_mutex);

	INIT_LIST_HEAD(&ar_sdio->scat_req);
	INIT_LIST_HEAD(&ar_sdio->bus_req_freeq);
	INIT_LIST_HEAD(&ar_sdio->wr_asyncq);

	INIT_WORK(&ar_sdio->wr_async_work, ath6kl_sdio_write_async_work);

	init_waitqueue_head(&ar_sdio->irq_wq);

	for (count = 0; count < BUS_REQUEST_MAX_NUM; count++)
		ath6kl_sdio_free_bus_req(ar_sdio, &ar_sdio->bus_req[count]);

	ar = ath6kl_core_create(&ar_sdio->func->dev);
	if (!ar) {
		ath6kl_err("Failed to alloc ath6kl core\n");
		ret = -ENOMEM;
		goto err_dma;
	}

	ar_sdio->ar = ar;
	ar->hif_type = ATH6KL_HIF_TYPE_SDIO;
	ar->hif_priv = ar_sdio;
	ar->hif_ops = &ath6kl_sdio_ops;
	ar->bmi.max_data_size = 256;

	ath6kl_sdio_set_mbox_info(ar);

	ret = ath6kl_sdio_config(ar);
	if (ret) {
		ath6kl_err("Failed to config sdio: %d\n", ret);
		goto err_core_alloc;
	}

	ret = ath6kl_core_init(ar, ATH6KL_HTC_TYPE_MBOX);
	if (ret) {
		ath6kl_err("Failed to init ath6kl core\n");
		goto err_core_alloc;
	}

	return ret;

err_core_alloc:
	ath6kl_core_destroy(ar_sdio->ar);
err_dma:
	kfree(ar_sdio->dma_buffer);
err_hif:
	kfree(ar_sdio);

	return ret;
}