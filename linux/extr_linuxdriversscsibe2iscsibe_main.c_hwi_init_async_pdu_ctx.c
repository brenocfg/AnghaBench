#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct hwi_controller {TYPE_17__* phwi_ctxt; } ;
struct TYPE_36__ {scalar_t__ address; } ;
struct TYPE_19__ {TYPE_9__ a64; } ;
struct TYPE_20__ {TYPE_10__ u; } ;
struct hd_async_handle {int cri; int is_header; unsigned int index; TYPE_11__ pa; void* pbuffer; int /*<<< orphan*/  link; } ;
struct TYPE_32__ {int /*<<< orphan*/  list; } ;
struct hd_async_entry {struct hd_async_handle* data; TYPE_5__ wq; struct hd_async_handle* header; } ;
struct TYPE_21__ {scalar_t__ address; } ;
struct TYPE_22__ {TYPE_12__ a64; } ;
struct TYPE_23__ {TYPE_13__ u; } ;
struct TYPE_24__ {unsigned int buffer_size; TYPE_14__ pa_base; scalar_t__ va_base; scalar_t__ pi; scalar_t__ handle_base; scalar_t__ ring_base; } ;
struct TYPE_28__ {scalar_t__ address; } ;
struct TYPE_29__ {TYPE_1__ a64; } ;
struct TYPE_30__ {TYPE_2__ u; } ;
struct TYPE_31__ {unsigned int buffer_size; TYPE_3__ pa_base; scalar_t__ va_base; scalar_t__ handle_base; scalar_t__ ring_base; scalar_t__ pi; } ;
struct hd_async_context {unsigned int num_entries; struct hd_async_entry* async_entry; TYPE_15__ async_data; TYPE_4__ async_header; } ;
struct hba_parameters {unsigned int defpdu_hdr_sz; unsigned int defpdu_data_sz; } ;
struct TYPE_25__ {int /*<<< orphan*/  ulp_supported; } ;
struct beiscsi_hba {struct hba_parameters params; scalar_t__ init_mem; struct hwi_controller* phwi_ctrlr; TYPE_16__ fw_config; } ;
struct be_mem_descriptor {TYPE_18__* mem_array; } ;
struct TYPE_33__ {scalar_t__ address; } ;
struct TYPE_34__ {TYPE_6__ a64; } ;
struct TYPE_35__ {TYPE_7__ u; } ;
struct TYPE_27__ {unsigned int size; TYPE_8__ bus_address; scalar_t__ virtual_address; } ;
struct TYPE_26__ {struct hd_async_context** pasync_ctx; } ;

/* Variables and functions */
 unsigned int BEISCSI_ASYNC_HDQ_SIZE (struct beiscsi_hba*,size_t) ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 size_t BEISCSI_ULP_COUNT ; 
 scalar_t__ HWI_MEM_ASYNC_DATA_BUF_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_DATA_HANDLE_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_DATA_RING_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_HEADER_BUF_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_HEADER_HANDLE_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_HEADER_RING_ULP0 ; 
 scalar_t__ HWI_MEM_ASYNC_PDU_CONTEXT_ULP0 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 size_t MEM_DESCR_OFFSET ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  memset (struct hd_async_context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwi_init_async_pdu_ctx(struct beiscsi_hba *phba)
{
	uint8_t ulp_num;
	struct hwi_controller *phwi_ctrlr;
	struct hba_parameters *p = &phba->params;
	struct hd_async_context *pasync_ctx;
	struct hd_async_handle *pasync_header_h, *pasync_data_h;
	unsigned int index, idx, num_per_mem, num_async_data;
	struct be_mem_descriptor *mem_descr;

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, &phba->fw_config.ulp_supported)) {
			/* get async_ctx for each ULP */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += (HWI_MEM_ASYNC_PDU_CONTEXT_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET));

			phwi_ctrlr = phba->phwi_ctrlr;
			phwi_ctrlr->phwi_ctxt->pasync_ctx[ulp_num] =
				(struct hd_async_context *)
				 mem_descr->mem_array[0].virtual_address;

			pasync_ctx = phwi_ctrlr->phwi_ctxt->pasync_ctx[ulp_num];
			memset(pasync_ctx, 0, sizeof(*pasync_ctx));

			pasync_ctx->async_entry =
					(struct hd_async_entry *)
					((long unsigned int)pasync_ctx +
					sizeof(struct hd_async_context));

			pasync_ctx->num_entries = BEISCSI_ASYNC_HDQ_SIZE(phba,
						  ulp_num);
			/* setup header buffers */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_HEADER_BUF_ULP0 +
				(ulp_num * MEM_DESCR_OFFSET);
			if (mem_descr->mem_array[0].virtual_address) {
				beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
					    "BM_%d : hwi_init_async_pdu_ctx"
					    " HWI_MEM_ASYNC_HEADER_BUF_ULP%d va=%p\n",
					    ulp_num,
					    mem_descr->mem_array[0].
					    virtual_address);
			} else
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			pasync_ctx->async_header.pi = 0;
			pasync_ctx->async_header.buffer_size = p->defpdu_hdr_sz;
			pasync_ctx->async_header.va_base =
				mem_descr->mem_array[0].virtual_address;

			pasync_ctx->async_header.pa_base.u.a64.address =
				mem_descr->mem_array[0].
				bus_address.u.a64.address;

			/* setup header buffer sgls */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_HEADER_RING_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET);
			if (mem_descr->mem_array[0].virtual_address) {
				beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
					    "BM_%d : hwi_init_async_pdu_ctx"
					    " HWI_MEM_ASYNC_HEADER_RING_ULP%d va=%p\n",
					    ulp_num,
					    mem_descr->mem_array[0].
					    virtual_address);
			} else
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			pasync_ctx->async_header.ring_base =
				mem_descr->mem_array[0].virtual_address;

			/* setup header buffer handles */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_HEADER_HANDLE_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET);
			if (mem_descr->mem_array[0].virtual_address) {
				beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
					    "BM_%d : hwi_init_async_pdu_ctx"
					    " HWI_MEM_ASYNC_HEADER_HANDLE_ULP%d va=%p\n",
					    ulp_num,
					    mem_descr->mem_array[0].
					    virtual_address);
			} else
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			pasync_ctx->async_header.handle_base =
				mem_descr->mem_array[0].virtual_address;

			/* setup data buffer sgls */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_DATA_RING_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET);
			if (mem_descr->mem_array[0].virtual_address) {
				beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
					    "BM_%d : hwi_init_async_pdu_ctx"
					    " HWI_MEM_ASYNC_DATA_RING_ULP%d va=%p\n",
					    ulp_num,
					    mem_descr->mem_array[0].
					    virtual_address);
			} else
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			pasync_ctx->async_data.ring_base =
				mem_descr->mem_array[0].virtual_address;

			/* setup data buffer handles */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_DATA_HANDLE_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET);
			if (!mem_descr->mem_array[0].virtual_address)
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			pasync_ctx->async_data.handle_base =
				mem_descr->mem_array[0].virtual_address;

			pasync_header_h =
				(struct hd_async_handle *)
				pasync_ctx->async_header.handle_base;
			pasync_data_h =
				(struct hd_async_handle *)
				pasync_ctx->async_data.handle_base;

			/* setup data buffers */
			mem_descr = (struct be_mem_descriptor *)phba->init_mem;
			mem_descr += HWI_MEM_ASYNC_DATA_BUF_ULP0 +
				     (ulp_num * MEM_DESCR_OFFSET);
			if (mem_descr->mem_array[0].virtual_address) {
				beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
					    "BM_%d : hwi_init_async_pdu_ctx"
					    " HWI_MEM_ASYNC_DATA_BUF_ULP%d va=%p\n",
					    ulp_num,
					    mem_descr->mem_array[0].
					    virtual_address);
			} else
				beiscsi_log(phba, KERN_WARNING,
					    BEISCSI_LOG_INIT,
					    "BM_%d : No Virtual address for ULP : %d\n",
					    ulp_num);

			idx = 0;
			pasync_ctx->async_data.pi = 0;
			pasync_ctx->async_data.buffer_size = p->defpdu_data_sz;
			pasync_ctx->async_data.va_base =
				mem_descr->mem_array[idx].virtual_address;
			pasync_ctx->async_data.pa_base.u.a64.address =
				mem_descr->mem_array[idx].
				bus_address.u.a64.address;

			num_async_data = ((mem_descr->mem_array[idx].size) /
					phba->params.defpdu_data_sz);
			num_per_mem = 0;

			for (index = 0;	index < BEISCSI_ASYNC_HDQ_SIZE
					(phba, ulp_num); index++) {
				pasync_header_h->cri = -1;
				pasync_header_h->is_header = 1;
				pasync_header_h->index = index;
				INIT_LIST_HEAD(&pasync_header_h->link);
				pasync_header_h->pbuffer =
					(void *)((unsigned long)
						 (pasync_ctx->
						  async_header.va_base) +
						 (p->defpdu_hdr_sz * index));

				pasync_header_h->pa.u.a64.address =
					pasync_ctx->async_header.pa_base.u.a64.
					address + (p->defpdu_hdr_sz * index);

				pasync_ctx->async_entry[index].header =
					pasync_header_h;
				pasync_header_h++;
				INIT_LIST_HEAD(&pasync_ctx->async_entry[index].
						wq.list);

				pasync_data_h->cri = -1;
				pasync_data_h->is_header = 0;
				pasync_data_h->index = index;
				INIT_LIST_HEAD(&pasync_data_h->link);

				if (!num_async_data) {
					num_per_mem = 0;
					idx++;
					pasync_ctx->async_data.va_base =
						mem_descr->mem_array[idx].
						virtual_address;
					pasync_ctx->async_data.pa_base.u.
						a64.address =
						mem_descr->mem_array[idx].
						bus_address.u.a64.address;
					num_async_data =
						((mem_descr->mem_array[idx].
						  size) /
						 phba->params.defpdu_data_sz);
				}
				pasync_data_h->pbuffer =
					(void *)((unsigned long)
					(pasync_ctx->async_data.va_base) +
					(p->defpdu_data_sz * num_per_mem));

				pasync_data_h->pa.u.a64.address =
					pasync_ctx->async_data.pa_base.u.a64.
					address + (p->defpdu_data_sz *
					num_per_mem);
				num_per_mem++;
				num_async_data--;

				pasync_ctx->async_entry[index].data =
					pasync_data_h;
				pasync_data_h++;
			}
		}
	}

	return 0;
}