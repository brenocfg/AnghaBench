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
typedef  size_t uint8_t ;
struct phys_addr {int dummy; } ;
struct hwi_controller {int dummy; } ;
struct hwi_context_memory {struct be_queue_info* be_def_hdrq; struct be_queue_info* be_cq; } ;
struct TYPE_10__ {int /*<<< orphan*/  defpdu_hdr_sz; } ;
struct beiscsi_hba {TYPE_5__ params; int /*<<< orphan*/  ctrl; struct be_mem_descriptor* init_mem; } ;
struct be_dma_mem {unsigned long dma; } ;
struct be_queue_info {int /*<<< orphan*/  id; struct be_dma_mem dma_mem; } ;
struct be_mem_descriptor {TYPE_4__* mem_array; } ;
struct TYPE_6__ {scalar_t__ address; } ;
struct TYPE_7__ {TYPE_1__ a64; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {int size; TYPE_3__ bus_address; void* virtual_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_DEFQ_HDR ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 scalar_t__ HWI_MEM_ASYNC_HEADER_RING_ULP0 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 size_t MEM_DESCR_OFFSET ; 
 int be_cmd_create_default_pdu_queue (int /*<<< orphan*/ *,struct be_queue_info*,struct be_queue_info*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int be_fill_queue (struct be_queue_info*,int,int,void*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 

__attribute__((used)) static int
beiscsi_create_def_hdr(struct beiscsi_hba *phba,
		       struct hwi_context_memory *phwi_context,
		       struct hwi_controller *phwi_ctrlr,
		       unsigned int def_pdu_ring_sz, uint8_t ulp_num)
{
	unsigned int idx;
	int ret;
	struct be_queue_info *dq, *cq;
	struct be_dma_mem *mem;
	struct be_mem_descriptor *mem_descr;
	void *dq_vaddress;

	idx = 0;
	dq = &phwi_context->be_def_hdrq[ulp_num];
	cq = &phwi_context->be_cq[0];
	mem = &dq->dma_mem;
	mem_descr = phba->init_mem;
	mem_descr += HWI_MEM_ASYNC_HEADER_RING_ULP0 +
		    (ulp_num * MEM_DESCR_OFFSET);
	dq_vaddress = mem_descr->mem_array[idx].virtual_address;
	ret = be_fill_queue(dq, mem_descr->mem_array[0].size /
			    sizeof(struct phys_addr),
			    sizeof(struct phys_addr), dq_vaddress);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : be_fill_queue Failed for DEF PDU HDR on ULP : %d\n",
			    ulp_num);

		return ret;
	}
	mem->dma = (unsigned long)mem_descr->mem_array[idx].
				  bus_address.u.a64.address;
	ret = be_cmd_create_default_pdu_queue(&phba->ctrl, cq, dq,
					      def_pdu_ring_sz,
					      phba->params.defpdu_hdr_sz,
					      BEISCSI_DEFQ_HDR, ulp_num);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : be_cmd_create_default_pdu_queue Failed DEFHDR on ULP : %d\n",
			    ulp_num);

		return ret;
	}

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BM_%d : iscsi hdr def pdu id for ULP : %d is %d\n",
		    ulp_num,
		    phwi_context->be_def_hdrq[ulp_num].id);
	return 0;
}