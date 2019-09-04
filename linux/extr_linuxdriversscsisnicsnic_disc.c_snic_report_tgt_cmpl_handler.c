#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct snic_tgt_id {int /*<<< orphan*/  tgt_id; } ;
struct snic_req_info {scalar_t__ sge_va; } ;
struct TYPE_6__ {int /*<<< orphan*/  tgt_cnt; } ;
struct TYPE_7__ {TYPE_1__ rpt_tgts_cmpl; } ;
struct snic_fw_req {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int rtgt_cnt; int /*<<< orphan*/ * rtgt_info; } ;
struct TYPE_8__ {int max_tgts; } ;
struct snic {int /*<<< orphan*/  tgt_work; TYPE_4__ disc; int /*<<< orphan*/  shost; TYPE_3__ fwinfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  event_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct snic_tgt_id*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* snic_glob ; 
 int /*<<< orphan*/  snic_io_hdr_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  snic_pci_unmap_rsp_buf (struct snic*,struct snic_req_info*) ; 
 int /*<<< orphan*/  snic_release_untagged_req (struct snic*,struct snic_req_info*) ; 

int
snic_report_tgt_cmpl_handler(struct snic *snic, struct snic_fw_req *fwreq)
{

	u8 typ, cmpl_stat;
	u32 cmnd_id, hid, tgt_cnt = 0;
	ulong ctx;
	struct snic_req_info *rqi = NULL;
	struct snic_tgt_id *tgtid;
	int i, ret = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &cmpl_stat, &cmnd_id, &hid, &ctx);
	rqi = (struct snic_req_info *) ctx;
	tgtid = (struct snic_tgt_id *) rqi->sge_va;

	tgt_cnt = le32_to_cpu(fwreq->u.rpt_tgts_cmpl.tgt_cnt);
	if (tgt_cnt == 0) {
		SNIC_HOST_ERR(snic->shost, "No Targets Found on this host.\n");
		ret = 1;

		goto end;
	}

	/* printing list of targets here */
	SNIC_HOST_INFO(snic->shost, "Target Count = %d\n", tgt_cnt);

	SNIC_BUG_ON(tgt_cnt > snic->fwinfo.max_tgts);

	for (i = 0; i < tgt_cnt; i++)
		SNIC_HOST_INFO(snic->shost,
			       "Tgt id = 0x%x\n",
			       le32_to_cpu(tgtid[i].tgt_id));

	/*
	 * Queue work for further processing,
	 * Response Buffer Memory is freed after creating targets
	 */
	snic->disc.rtgt_cnt = tgt_cnt;
	snic->disc.rtgt_info = (u8 *) tgtid;
	queue_work(snic_glob->event_q, &snic->tgt_work);
	ret = 0;

end:
	/* Unmap Response Buffer */
	snic_pci_unmap_rsp_buf(snic, rqi);
	if (ret)
		kfree(tgtid);

	rqi->sge_va = 0;
	snic_release_untagged_req(snic, rqi);

	return ret;
}