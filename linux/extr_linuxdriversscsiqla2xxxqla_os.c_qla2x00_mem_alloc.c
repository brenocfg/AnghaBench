#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct sns_cmd_pkt {int dummy; } ;
struct rsp_que {int length; scalar_t__ dma; int /*<<< orphan*/ * ring; struct rsp_que* req; struct rsp_que* rsp; struct qla_hw_data* hw; } ;
struct req_que {int length; scalar_t__ dma; int /*<<< orphan*/ * ring; struct req_que* req; struct req_que* rsp; struct qla_hw_data* hw; } ;
struct qla_npiv_entry {int dummy; } ;
struct qla_hw_data {int init_cb_size; scalar_t__ init_cb_dma; int /*<<< orphan*/ * init_cb; TYPE_1__* pdev; scalar_t__ gid_list_dma; int /*<<< orphan*/ * gid_list; int /*<<< orphan*/ * srb_mempool; int /*<<< orphan*/ * ctx_mempool; struct rsp_que* nvram; int /*<<< orphan*/ * s_dma_pool; int /*<<< orphan*/ * dl_dma_pool; int /*<<< orphan*/ * fcp_cmnd_dma_pool; scalar_t__ sns_cmd_dma; int /*<<< orphan*/ * sns_cmd; scalar_t__ ms_iocb_dma; int /*<<< orphan*/ * ms_iocb; scalar_t__ ct_sns_dma; int /*<<< orphan*/ * ct_sns; struct rsp_que* npiv_info; scalar_t__ ex_init_cb_dma; int /*<<< orphan*/ * ex_init_cb; scalar_t__ async_pd_dma; int /*<<< orphan*/ * async_pd; struct rsp_que* loop_id_map; void* sfp_data; scalar_t__ sfp_data_dma; int /*<<< orphan*/  vp_list; int /*<<< orphan*/  gbl_dsd_list; scalar_t__ nvram_npiv_size; } ;
struct ct_sns_pkt {int dummy; } ;
struct ct6_dsd {int dummy; } ;
typedef  int /*<<< orphan*/  response_t ;
typedef  int /*<<< orphan*/  request_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_POOL_SIZE ; 
 int /*<<< orphan*/  DSD_LIST_DMA_POOL_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCP_CMND_DMA_POOL_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_P3P_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2031 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  LOOPID_MAP_SIZE ; 
 int MAX_NVRAM_SIZE ; 
 char* QLA2XXX_DRIVER_NAME ; 
 int SFP_DEV_SIZE ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  SRB_MIN_REQ ; 
 scalar_t__ ctx_cachep ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 void* dma_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rsp_que*) ; 
 scalar_t__ kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* mempool_create_slab_pool (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ ql2xenabledif ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_pci (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int qla2x00_gid_list_size (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_set_reserved_loop_ids (struct qla_hw_data*) ; 
 scalar_t__ qlt_mem_alloc (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qlt_mem_free (struct qla_hw_data*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 scalar_t__ srb_cachep ; 

__attribute__((used)) static int
qla2x00_mem_alloc(struct qla_hw_data *ha, uint16_t req_len, uint16_t rsp_len,
	struct req_que **req, struct rsp_que **rsp)
{
	char	name[16];

	ha->init_cb = dma_alloc_coherent(&ha->pdev->dev, ha->init_cb_size,
		&ha->init_cb_dma, GFP_KERNEL);
	if (!ha->init_cb)
		goto fail;

	if (qlt_mem_alloc(ha) < 0)
		goto fail_free_init_cb;

	ha->gid_list = dma_alloc_coherent(&ha->pdev->dev,
		qla2x00_gid_list_size(ha), &ha->gid_list_dma, GFP_KERNEL);
	if (!ha->gid_list)
		goto fail_free_tgt_mem;

	ha->srb_mempool = mempool_create_slab_pool(SRB_MIN_REQ, srb_cachep);
	if (!ha->srb_mempool)
		goto fail_free_gid_list;

	if (IS_P3P_TYPE(ha)) {
		/* Allocate cache for CT6 Ctx. */
		if (!ctx_cachep) {
			ctx_cachep = kmem_cache_create("qla2xxx_ctx",
				sizeof(struct ct6_dsd), 0,
				SLAB_HWCACHE_ALIGN, NULL);
			if (!ctx_cachep)
				goto fail_free_srb_mempool;
		}
		ha->ctx_mempool = mempool_create_slab_pool(SRB_MIN_REQ,
			ctx_cachep);
		if (!ha->ctx_mempool)
			goto fail_free_srb_mempool;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0021,
		    "ctx_cachep=%p ctx_mempool=%p.\n",
		    ctx_cachep, ha->ctx_mempool);
	}

	/* Get memory for cached NVRAM */
	ha->nvram = kzalloc(MAX_NVRAM_SIZE, GFP_KERNEL);
	if (!ha->nvram)
		goto fail_free_ctx_mempool;

	snprintf(name, sizeof(name), "%s_%d", QLA2XXX_DRIVER_NAME,
		ha->pdev->device);
	ha->s_dma_pool = dma_pool_create(name, &ha->pdev->dev,
		DMA_POOL_SIZE, 8, 0);
	if (!ha->s_dma_pool)
		goto fail_free_nvram;

	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0022,
	    "init_cb=%p gid_list=%p, srb_mempool=%p s_dma_pool=%p.\n",
	    ha->init_cb, ha->gid_list, ha->srb_mempool, ha->s_dma_pool);

	if (IS_P3P_TYPE(ha) || ql2xenabledif) {
		ha->dl_dma_pool = dma_pool_create(name, &ha->pdev->dev,
			DSD_LIST_DMA_POOL_SIZE, 8, 0);
		if (!ha->dl_dma_pool) {
			ql_log_pci(ql_log_fatal, ha->pdev, 0x0023,
			    "Failed to allocate memory for dl_dma_pool.\n");
			goto fail_s_dma_pool;
		}

		ha->fcp_cmnd_dma_pool = dma_pool_create(name, &ha->pdev->dev,
			FCP_CMND_DMA_POOL_SIZE, 8, 0);
		if (!ha->fcp_cmnd_dma_pool) {
			ql_log_pci(ql_log_fatal, ha->pdev, 0x0024,
			    "Failed to allocate memory for fcp_cmnd_dma_pool.\n");
			goto fail_dl_dma_pool;
		}
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0025,
		    "dl_dma_pool=%p fcp_cmnd_dma_pool=%p.\n",
		    ha->dl_dma_pool, ha->fcp_cmnd_dma_pool);
	}

	/* Allocate memory for SNS commands */
	if (IS_QLA2100(ha) || IS_QLA2200(ha)) {
	/* Get consistent memory allocated for SNS commands */
		ha->sns_cmd = dma_alloc_coherent(&ha->pdev->dev,
		sizeof(struct sns_cmd_pkt), &ha->sns_cmd_dma, GFP_KERNEL);
		if (!ha->sns_cmd)
			goto fail_dma_pool;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0026,
		    "sns_cmd: %p.\n", ha->sns_cmd);
	} else {
	/* Get consistent memory allocated for MS IOCB */
		ha->ms_iocb = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
			&ha->ms_iocb_dma);
		if (!ha->ms_iocb)
			goto fail_dma_pool;
	/* Get consistent memory allocated for CT SNS commands */
		ha->ct_sns = dma_alloc_coherent(&ha->pdev->dev,
			sizeof(struct ct_sns_pkt), &ha->ct_sns_dma, GFP_KERNEL);
		if (!ha->ct_sns)
			goto fail_free_ms_iocb;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0027,
		    "ms_iocb=%p ct_sns=%p.\n",
		    ha->ms_iocb, ha->ct_sns);
	}

	/* Allocate memory for request ring */
	*req = kzalloc(sizeof(struct req_que), GFP_KERNEL);
	if (!*req) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0028,
		    "Failed to allocate memory for req.\n");
		goto fail_req;
	}
	(*req)->length = req_len;
	(*req)->ring = dma_alloc_coherent(&ha->pdev->dev,
		((*req)->length + 1) * sizeof(request_t),
		&(*req)->dma, GFP_KERNEL);
	if (!(*req)->ring) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0029,
		    "Failed to allocate memory for req_ring.\n");
		goto fail_req_ring;
	}
	/* Allocate memory for response ring */
	*rsp = kzalloc(sizeof(struct rsp_que), GFP_KERNEL);
	if (!*rsp) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x002a,
		    "Failed to allocate memory for rsp.\n");
		goto fail_rsp;
	}
	(*rsp)->hw = ha;
	(*rsp)->length = rsp_len;
	(*rsp)->ring = dma_alloc_coherent(&ha->pdev->dev,
		((*rsp)->length + 1) * sizeof(response_t),
		&(*rsp)->dma, GFP_KERNEL);
	if (!(*rsp)->ring) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x002b,
		    "Failed to allocate memory for rsp_ring.\n");
		goto fail_rsp_ring;
	}
	(*req)->rsp = *rsp;
	(*rsp)->req = *req;
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002c,
	    "req=%p req->length=%d req->ring=%p rsp=%p "
	    "rsp->length=%d rsp->ring=%p.\n",
	    *req, (*req)->length, (*req)->ring, *rsp, (*rsp)->length,
	    (*rsp)->ring);
	/* Allocate memory for NVRAM data for vports */
	if (ha->nvram_npiv_size) {
		ha->npiv_info = kcalloc(ha->nvram_npiv_size,
					sizeof(struct qla_npiv_entry),
					GFP_KERNEL);
		if (!ha->npiv_info) {
			ql_log_pci(ql_log_fatal, ha->pdev, 0x002d,
			    "Failed to allocate memory for npiv_info.\n");
			goto fail_npiv_info;
		}
	} else
		ha->npiv_info = NULL;

	/* Get consistent memory allocated for EX-INIT-CB. */
	if (IS_CNA_CAPABLE(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha)) {
		ha->ex_init_cb = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
		    &ha->ex_init_cb_dma);
		if (!ha->ex_init_cb)
			goto fail_ex_init_cb;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002e,
		    "ex_init_cb=%p.\n", ha->ex_init_cb);
	}

	INIT_LIST_HEAD(&ha->gbl_dsd_list);

	/* Get consistent memory allocated for Async Port-Database. */
	if (!IS_FWI2_CAPABLE(ha)) {
		ha->async_pd = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
			&ha->async_pd_dma);
		if (!ha->async_pd)
			goto fail_async_pd;
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x002f,
		    "async_pd=%p.\n", ha->async_pd);
	}

	INIT_LIST_HEAD(&ha->vp_list);

	/* Allocate memory for our loop_id bitmap */
	ha->loop_id_map = kcalloc(BITS_TO_LONGS(LOOPID_MAP_SIZE),
				  sizeof(long),
				  GFP_KERNEL);
	if (!ha->loop_id_map)
		goto fail_loop_id_map;
	else {
		qla2x00_set_reserved_loop_ids(ha);
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0123,
		    "loop_id_map=%p.\n", ha->loop_id_map);
	}

	ha->sfp_data = dma_alloc_coherent(&ha->pdev->dev,
	    SFP_DEV_SIZE, &ha->sfp_data_dma, GFP_KERNEL);
	if (!ha->sfp_data) {
		ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011b,
		    "Unable to allocate memory for SFP read-data.\n");
		goto fail_sfp_data;
	}

	return 0;

fail_sfp_data:
	kfree(ha->loop_id_map);
fail_loop_id_map:
	dma_pool_free(ha->s_dma_pool, ha->async_pd, ha->async_pd_dma);
fail_async_pd:
	dma_pool_free(ha->s_dma_pool, ha->ex_init_cb, ha->ex_init_cb_dma);
fail_ex_init_cb:
	kfree(ha->npiv_info);
fail_npiv_info:
	dma_free_coherent(&ha->pdev->dev, ((*rsp)->length + 1) *
		sizeof(response_t), (*rsp)->ring, (*rsp)->dma);
	(*rsp)->ring = NULL;
	(*rsp)->dma = 0;
fail_rsp_ring:
	kfree(*rsp);
	*rsp = NULL;
fail_rsp:
	dma_free_coherent(&ha->pdev->dev, ((*req)->length + 1) *
		sizeof(request_t), (*req)->ring, (*req)->dma);
	(*req)->ring = NULL;
	(*req)->dma = 0;
fail_req_ring:
	kfree(*req);
	*req = NULL;
fail_req:
	dma_free_coherent(&ha->pdev->dev, sizeof(struct ct_sns_pkt),
		ha->ct_sns, ha->ct_sns_dma);
	ha->ct_sns = NULL;
	ha->ct_sns_dma = 0;
fail_free_ms_iocb:
	dma_pool_free(ha->s_dma_pool, ha->ms_iocb, ha->ms_iocb_dma);
	ha->ms_iocb = NULL;
	ha->ms_iocb_dma = 0;

	if (ha->sns_cmd)
		dma_free_coherent(&ha->pdev->dev, sizeof(struct sns_cmd_pkt),
		    ha->sns_cmd, ha->sns_cmd_dma);
fail_dma_pool:
	if (IS_QLA82XX(ha) || ql2xenabledif) {
		dma_pool_destroy(ha->fcp_cmnd_dma_pool);
		ha->fcp_cmnd_dma_pool = NULL;
	}
fail_dl_dma_pool:
	if (IS_QLA82XX(ha) || ql2xenabledif) {
		dma_pool_destroy(ha->dl_dma_pool);
		ha->dl_dma_pool = NULL;
	}
fail_s_dma_pool:
	dma_pool_destroy(ha->s_dma_pool);
	ha->s_dma_pool = NULL;
fail_free_nvram:
	kfree(ha->nvram);
	ha->nvram = NULL;
fail_free_ctx_mempool:
	if (ha->ctx_mempool)
		mempool_destroy(ha->ctx_mempool);
	ha->ctx_mempool = NULL;
fail_free_srb_mempool:
	if (ha->srb_mempool)
		mempool_destroy(ha->srb_mempool);
	ha->srb_mempool = NULL;
fail_free_gid_list:
	dma_free_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	ha->gid_list,
	ha->gid_list_dma);
	ha->gid_list = NULL;
	ha->gid_list_dma = 0;
fail_free_tgt_mem:
	qlt_mem_free(ha);
fail_free_init_cb:
	dma_free_coherent(&ha->pdev->dev, ha->init_cb_size, ha->init_cb,
	ha->init_cb_dma);
	ha->init_cb = NULL;
	ha->init_cb_dma = 0;
fail:
	ql_log(ql_log_fatal, NULL, 0x0030,
	    "Memory allocation failure.\n");
	return -ENOMEM;
}