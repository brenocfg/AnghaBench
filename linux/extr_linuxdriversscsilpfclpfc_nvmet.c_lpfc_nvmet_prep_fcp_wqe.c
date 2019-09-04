#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct sli4_sge {int abort_tag; int addr_hi; int addr_lo; int word2; void* sge_len; } ;
struct TYPE_27__ {int bdeSize; void* bdeFlags; } ;
struct TYPE_28__ {TYPE_13__ f; } ;
struct TYPE_29__ {void* addrHigh; void* addrLow; TYPE_14__ tus; } ;
struct TYPE_31__ {int response_len; int /*<<< orphan*/ * rsvd_12_15; struct sli4_sge wqe_com; TYPE_15__ bde; } ;
struct TYPE_42__ {void* bdeSize; void* bdeFlags; } ;
struct TYPE_43__ {TYPE_5__ f; } ;
struct TYPE_44__ {void* addrHigh; void* addrLow; TYPE_6__ tus; } ;
struct TYPE_26__ {int relative_offset; int /*<<< orphan*/  fcp_data_len; struct sli4_sge wqe_com; int /*<<< orphan*/  reserved; int /*<<< orphan*/  payload_offset_len; TYPE_7__ bde; } ;
struct TYPE_45__ {int bdeSize; void* bdeFlags; } ;
struct TYPE_46__ {TYPE_8__ f; } ;
struct TYPE_24__ {void* addrHigh; void* addrLow; TYPE_9__ tus; } ;
struct TYPE_25__ {int relative_offset; struct sli4_sge wqe_com; TYPE_10__ bde; } ;
union lpfc_wqe128 {int /*<<< orphan*/ * words; TYPE_17__ fcp_trsp; TYPE_12__ fcp_tsend; TYPE_11__ fcp_treceive; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_32__ {void* bdeFlags; int /*<<< orphan*/  bdeSize; } ;
struct TYPE_33__ {int w; TYPE_18__ f; } ;
struct ulp_bde64 {int addrLow; int addrHigh; TYPE_19__ tus; } ;
struct scatterlist {int dummy; } ;
struct nvmefc_tgt_fcp_req {int sg_cnt; int op; int rsplen; struct scatterlist* sg; int /*<<< orphan*/ * rspaddr; int /*<<< orphan*/  rspdma; int /*<<< orphan*/  transfer_length; } ;
struct lpfc_nvmet_tgtport {int /*<<< orphan*/  xmt_fcp_rsp; int /*<<< orphan*/  xmt_fcp_write; int /*<<< orphan*/  xmt_fcp_read; int /*<<< orphan*/  xmt_fcp_read_rsp; } ;
struct TYPE_34__ {struct nvmefc_tgt_fcp_req fcp_req; } ;
struct lpfc_nvmet_rcv_ctx {int oxid; scalar_t__ state; int entry_cnt; int offset; int /*<<< orphan*/  txrdy_phys; int /*<<< orphan*/ * txrdy; TYPE_4__* ctxbuf; struct lpfc_iocbq* wqeq; int /*<<< orphan*/  sid; TYPE_1__ ctx; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; size_t nlp_rpi; int nlp_flag; } ;
struct lpfc_iocbq {int sli4_xritag; int iotag; int retry; struct lpfc_nodelist* context1; scalar_t__ drvrTimeout; int /*<<< orphan*/  vport; union lpfc_wqe128 wqe; void* sli4_lxritag; } ;
struct TYPE_30__ {int* rpi_ids; } ;
struct lpfc_hba {int fc_ratov; int /*<<< orphan*/  pport; TYPE_16__ sli4_hba; int /*<<< orphan*/  cfg_enable_pbde; int /*<<< orphan*/  txrdy_payload_pool; TYPE_2__* targetport; int /*<<< orphan*/  cfg_nvme_seg_cnt; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_41__ {TYPE_3__* sglq; struct lpfc_iocbq* iocbq; } ;
struct TYPE_40__ {scalar_t__ sgl; } ;
struct TYPE_39__ {scalar_t__ private; } ;
struct TYPE_38__ {int max_sgl_segments; } ;
struct TYPE_37__ {int /*<<< orphan*/ * words; } ;
struct TYPE_36__ {int /*<<< orphan*/ * words; } ;
struct TYPE_35__ {int /*<<< orphan*/ * words; } ;

/* Variables and functions */
 void* BUFF_TYPE_BDE_64 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 scalar_t__ LPFC_DRVR_TIMEOUT ; 
 scalar_t__ LPFC_NVMET_STE_DATA ; 
 scalar_t__ LPFC_NVMET_STE_RCV ; 
 int LPFC_NVMET_SUCCESS_LEN ; 
 int LPFC_SGE_TYPE_DATA ; 
 int LPFC_SGE_TYPE_SKIP ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int NLP_SUPPRESS_RSP ; 
 void* NO_XRI ; 
#define  NVMET_FCOP_READDATA 131 
#define  NVMET_FCOP_READDATA_RSP 130 
#define  NVMET_FCOP_RSP 129 
#define  NVMET_FCOP_WRITEDATA 128 
 int TXRDY_PAYLOAD_LEN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/ * dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const,...) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int /*<<< orphan*/  lpfc_sli4_sge_offset ; 
 int /*<<< orphan*/  lpfc_sli4_sge_type ; 
 TYPE_23__ lpfc_tgttemplate ; 
 TYPE_22__ lpfc_treceive_cmd_template ; 
 TYPE_21__ lpfc_trsp_cmd_template ; 
 TYPE_20__ lpfc_tsend_cmd_template ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ulp_bde64*,int /*<<< orphan*/ ,int) ; 
 int putPaddrHigh (int /*<<< orphan*/ ) ; 
 int putPaddrLow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 void* sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  wqe_ar ; 
 int /*<<< orphan*/  wqe_ctxt_tag ; 
 int /*<<< orphan*/  wqe_irsp ; 
 int /*<<< orphan*/  wqe_irsplen ; 
 int /*<<< orphan*/  wqe_pbde ; 
 int /*<<< orphan*/  wqe_rcvoxid ; 
 int /*<<< orphan*/  wqe_reqtag ; 
 int /*<<< orphan*/  wqe_sup ; 
 int /*<<< orphan*/  wqe_wqes ; 
 int /*<<< orphan*/  wqe_xc ; 
 int /*<<< orphan*/  wqe_xri_tag ; 

__attribute__((used)) static struct lpfc_iocbq *
lpfc_nvmet_prep_fcp_wqe(struct lpfc_hba *phba,
			struct lpfc_nvmet_rcv_ctx *ctxp)
{
	struct nvmefc_tgt_fcp_req *rsp = &ctxp->ctx.fcp_req;
	struct lpfc_nvmet_tgtport *tgtp;
	struct sli4_sge *sgl;
	struct lpfc_nodelist *ndlp;
	struct lpfc_iocbq *nvmewqe;
	struct scatterlist *sgel;
	union lpfc_wqe128 *wqe;
	struct ulp_bde64 *bde;
	uint32_t *txrdy;
	dma_addr_t physaddr;
	int i, cnt;
	int do_pbde;
	int xc = 1;

	if (!lpfc_is_link_up(phba)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6107 NVMET prep FCP wqe: link err:"
				"NPORT x%x oxid x%x ste %d\n",
				ctxp->sid, ctxp->oxid, ctxp->state);
		return NULL;
	}

	ndlp = lpfc_findnode_did(phba->pport, ctxp->sid);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp) ||
	    ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	     (ndlp->nlp_state != NLP_STE_MAPPED_NODE))) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6108 NVMET prep FCP wqe: no ndlp: "
				"NPORT x%x oxid x%x ste %d\n",
				ctxp->sid, ctxp->oxid, ctxp->state);
		return NULL;
	}

	if (rsp->sg_cnt > lpfc_tgttemplate.max_sgl_segments) {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6109 NVMET prep FCP wqe: seg cnt err: "
				"NPORT x%x oxid x%x ste %d cnt %d\n",
				ctxp->sid, ctxp->oxid, ctxp->state,
				phba->cfg_nvme_seg_cnt);
		return NULL;
	}

	tgtp = (struct lpfc_nvmet_tgtport *)phba->targetport->private;
	nvmewqe = ctxp->wqeq;
	if (nvmewqe == NULL) {
		/* Allocate buffer for  command wqe */
		nvmewqe = ctxp->ctxbuf->iocbq;
		if (nvmewqe == NULL) {
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
					"6110 NVMET prep FCP wqe: No "
					"WQE: NPORT x%x oxid x%x ste %d\n",
					ctxp->sid, ctxp->oxid, ctxp->state);
			return NULL;
		}
		ctxp->wqeq = nvmewqe;
		xc = 0; /* create new XRI */
		nvmewqe->sli4_lxritag = NO_XRI;
		nvmewqe->sli4_xritag = NO_XRI;
	}

	/* Sanity check */
	if (((ctxp->state == LPFC_NVMET_STE_RCV) &&
	    (ctxp->entry_cnt == 1)) ||
	    (ctxp->state == LPFC_NVMET_STE_DATA)) {
		wqe = &nvmewqe->wqe;
	} else {
		lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
				"6111 Wrong state NVMET FCP: %d  cnt %d\n",
				ctxp->state, ctxp->entry_cnt);
		return NULL;
	}

	sgl  = (struct sli4_sge *)ctxp->ctxbuf->sglq->sgl;
	switch (rsp->op) {
	case NVMET_FCOP_READDATA:
	case NVMET_FCOP_READDATA_RSP:
		/* From the tsend template, initialize words 7 - 11 */
		memcpy(&wqe->words[7],
		       &lpfc_tsend_cmd_template.words[7],
		       sizeof(uint32_t) * 5);

		/* Words 0 - 2 : The first sg segment */
		sgel = &rsp->sg[0];
		physaddr = sg_dma_address(sgel);
		wqe->fcp_tsend.bde.tus.f.bdeFlags = BUFF_TYPE_BDE_64;
		wqe->fcp_tsend.bde.tus.f.bdeSize = sg_dma_len(sgel);
		wqe->fcp_tsend.bde.addrLow = cpu_to_le32(putPaddrLow(physaddr));
		wqe->fcp_tsend.bde.addrHigh =
			cpu_to_le32(putPaddrHigh(physaddr));

		/* Word 3 */
		wqe->fcp_tsend.payload_offset_len = 0;

		/* Word 4 */
		wqe->fcp_tsend.relative_offset = ctxp->offset;

		/* Word 5 */
		wqe->fcp_tsend.reserved = 0;

		/* Word 6 */
		bf_set(wqe_ctxt_tag, &wqe->fcp_tsend.wqe_com,
		       phba->sli4_hba.rpi_ids[ndlp->nlp_rpi]);
		bf_set(wqe_xri_tag, &wqe->fcp_tsend.wqe_com,
		       nvmewqe->sli4_xritag);

		/* Word 7 - set ar later */

		/* Word 8 */
		wqe->fcp_tsend.wqe_com.abort_tag = nvmewqe->iotag;

		/* Word 9 */
		bf_set(wqe_reqtag, &wqe->fcp_tsend.wqe_com, nvmewqe->iotag);
		bf_set(wqe_rcvoxid, &wqe->fcp_tsend.wqe_com, ctxp->oxid);

		/* Word 10 - set wqes later, in template xc=1 */
		if (!xc)
			bf_set(wqe_xc, &wqe->fcp_tsend.wqe_com, 0);

		/* Word 11 - set sup, irsp, irsplen later */
		do_pbde = 0;

		/* Word 12 */
		wqe->fcp_tsend.fcp_data_len = rsp->transfer_length;

		/* Setup 2 SKIP SGEs */
		sgl->addr_hi = 0;
		sgl->addr_lo = 0;
		sgl->word2 = 0;
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_SKIP);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = 0;
		sgl++;
		sgl->addr_hi = 0;
		sgl->addr_lo = 0;
		sgl->word2 = 0;
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_SKIP);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = 0;
		sgl++;
		if (rsp->op == NVMET_FCOP_READDATA_RSP) {
			atomic_inc(&tgtp->xmt_fcp_read_rsp);

			/* In template ar=1 wqes=0 sup=0 irsp=0 irsplen=0 */

			if (rsp->rsplen == LPFC_NVMET_SUCCESS_LEN) {
				if (ndlp->nlp_flag & NLP_SUPPRESS_RSP)
					bf_set(wqe_sup,
					       &wqe->fcp_tsend.wqe_com, 1);
			} else {
				bf_set(wqe_wqes, &wqe->fcp_tsend.wqe_com, 1);
				bf_set(wqe_irsp, &wqe->fcp_tsend.wqe_com, 1);
				bf_set(wqe_irsplen, &wqe->fcp_tsend.wqe_com,
				       ((rsp->rsplen >> 2) - 1));
				memcpy(&wqe->words[16], rsp->rspaddr,
				       rsp->rsplen);
			}
		} else {
			atomic_inc(&tgtp->xmt_fcp_read);

			/* In template ar=1 wqes=0 sup=0 irsp=0 irsplen=0 */
			bf_set(wqe_ar, &wqe->fcp_tsend.wqe_com, 0);
		}
		break;

	case NVMET_FCOP_WRITEDATA:
		/* From the treceive template, initialize words 3 - 11 */
		memcpy(&wqe->words[3],
		       &lpfc_treceive_cmd_template.words[3],
		       sizeof(uint32_t) * 9);

		/* Words 0 - 2 : The first sg segment */
		txrdy = dma_pool_alloc(phba->txrdy_payload_pool,
				       GFP_KERNEL, &physaddr);
		if (!txrdy) {
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
					"6041 Bad txrdy buffer: oxid x%x\n",
					ctxp->oxid);
			return NULL;
		}
		ctxp->txrdy = txrdy;
		ctxp->txrdy_phys = physaddr;
		wqe->fcp_treceive.bde.tus.f.bdeFlags = BUFF_TYPE_BDE_64;
		wqe->fcp_treceive.bde.tus.f.bdeSize = TXRDY_PAYLOAD_LEN;
		wqe->fcp_treceive.bde.addrLow =
			cpu_to_le32(putPaddrLow(physaddr));
		wqe->fcp_treceive.bde.addrHigh =
			cpu_to_le32(putPaddrHigh(physaddr));

		/* Word 4 */
		wqe->fcp_treceive.relative_offset = ctxp->offset;

		/* Word 6 */
		bf_set(wqe_ctxt_tag, &wqe->fcp_treceive.wqe_com,
		       phba->sli4_hba.rpi_ids[ndlp->nlp_rpi]);
		bf_set(wqe_xri_tag, &wqe->fcp_treceive.wqe_com,
		       nvmewqe->sli4_xritag);

		/* Word 7 */

		/* Word 8 */
		wqe->fcp_treceive.wqe_com.abort_tag = nvmewqe->iotag;

		/* Word 9 */
		bf_set(wqe_reqtag, &wqe->fcp_treceive.wqe_com, nvmewqe->iotag);
		bf_set(wqe_rcvoxid, &wqe->fcp_treceive.wqe_com, ctxp->oxid);

		/* Word 10 - in template xc=1 */
		if (!xc)
			bf_set(wqe_xc, &wqe->fcp_treceive.wqe_com, 0);

		/* Word 11 - set pbde later */
		if (phba->cfg_enable_pbde) {
			do_pbde = 1;
		} else {
			bf_set(wqe_pbde, &wqe->fcp_treceive.wqe_com, 0);
			do_pbde = 0;
		}

		/* Word 12 */
		wqe->fcp_tsend.fcp_data_len = rsp->transfer_length;

		/* Setup 1 TXRDY and 1 SKIP SGE */
		txrdy[0] = 0;
		txrdy[1] = cpu_to_be32(rsp->transfer_length);
		txrdy[2] = 0;

		sgl->addr_hi = putPaddrHigh(physaddr);
		sgl->addr_lo = putPaddrLow(physaddr);
		sgl->word2 = 0;
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_DATA);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = cpu_to_le32(TXRDY_PAYLOAD_LEN);
		sgl++;
		sgl->addr_hi = 0;
		sgl->addr_lo = 0;
		sgl->word2 = 0;
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_SKIP);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = 0;
		sgl++;
		atomic_inc(&tgtp->xmt_fcp_write);
		break;

	case NVMET_FCOP_RSP:
		/* From the treceive template, initialize words 4 - 11 */
		memcpy(&wqe->words[4],
		       &lpfc_trsp_cmd_template.words[4],
		       sizeof(uint32_t) * 8);

		/* Words 0 - 2 */
		physaddr = rsp->rspdma;
		wqe->fcp_trsp.bde.tus.f.bdeFlags = BUFF_TYPE_BDE_64;
		wqe->fcp_trsp.bde.tus.f.bdeSize = rsp->rsplen;
		wqe->fcp_trsp.bde.addrLow =
			cpu_to_le32(putPaddrLow(physaddr));
		wqe->fcp_trsp.bde.addrHigh =
			cpu_to_le32(putPaddrHigh(physaddr));

		/* Word 3 */
		wqe->fcp_trsp.response_len = rsp->rsplen;

		/* Word 6 */
		bf_set(wqe_ctxt_tag, &wqe->fcp_trsp.wqe_com,
		       phba->sli4_hba.rpi_ids[ndlp->nlp_rpi]);
		bf_set(wqe_xri_tag, &wqe->fcp_trsp.wqe_com,
		       nvmewqe->sli4_xritag);

		/* Word 7 */

		/* Word 8 */
		wqe->fcp_trsp.wqe_com.abort_tag = nvmewqe->iotag;

		/* Word 9 */
		bf_set(wqe_reqtag, &wqe->fcp_trsp.wqe_com, nvmewqe->iotag);
		bf_set(wqe_rcvoxid, &wqe->fcp_trsp.wqe_com, ctxp->oxid);

		/* Word 10 */
		if (xc)
			bf_set(wqe_xc, &wqe->fcp_trsp.wqe_com, 1);

		/* Word 11 */
		/* In template wqes=0 irsp=0 irsplen=0 - good response */
		if (rsp->rsplen != LPFC_NVMET_SUCCESS_LEN) {
			/* Bad response - embed it */
			bf_set(wqe_wqes, &wqe->fcp_trsp.wqe_com, 1);
			bf_set(wqe_irsp, &wqe->fcp_trsp.wqe_com, 1);
			bf_set(wqe_irsplen, &wqe->fcp_trsp.wqe_com,
			       ((rsp->rsplen >> 2) - 1));
			memcpy(&wqe->words[16], rsp->rspaddr, rsp->rsplen);
		}
		do_pbde = 0;

		/* Word 12 */
		wqe->fcp_trsp.rsvd_12_15[0] = 0;

		/* Use rspbuf, NOT sg list */
		rsp->sg_cnt = 0;
		sgl->word2 = 0;
		atomic_inc(&tgtp->xmt_fcp_rsp);
		break;

	default:
		lpfc_printf_log(phba, KERN_INFO, LOG_NVME_IOERR,
				"6064 Unknown Rsp Op %d\n",
				rsp->op);
		return NULL;
	}

	nvmewqe->retry = 1;
	nvmewqe->vport = phba->pport;
	nvmewqe->drvrTimeout = (phba->fc_ratov * 3) + LPFC_DRVR_TIMEOUT;
	nvmewqe->context1 = ndlp;

	for (i = 0; i < rsp->sg_cnt; i++) {
		sgel = &rsp->sg[i];
		physaddr = sg_dma_address(sgel);
		cnt = sg_dma_len(sgel);
		sgl->addr_hi = putPaddrHigh(physaddr);
		sgl->addr_lo = putPaddrLow(physaddr);
		sgl->word2 = 0;
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_DATA);
		bf_set(lpfc_sli4_sge_offset, sgl, ctxp->offset);
		if ((i+1) == rsp->sg_cnt)
			bf_set(lpfc_sli4_sge_last, sgl, 1);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = cpu_to_le32(cnt);
		if (i == 0) {
			bde = (struct ulp_bde64 *)&wqe->words[13];
			if (do_pbde) {
				/* Words 13-15  (PBDE) */
				bde->addrLow = sgl->addr_lo;
				bde->addrHigh = sgl->addr_hi;
				bde->tus.f.bdeSize =
					le32_to_cpu(sgl->sge_len);
				bde->tus.f.bdeFlags = BUFF_TYPE_BDE_64;
				bde->tus.w = cpu_to_le32(bde->tus.w);
			} else {
				memset(bde, 0, sizeof(struct ulp_bde64));
			}
		}
		sgl++;
		ctxp->offset += cnt;
	}
	ctxp->state = LPFC_NVMET_STE_DATA;
	ctxp->entry_cnt++;
	return nvmewqe;
}