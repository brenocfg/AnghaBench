#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct ulp_cid_info {size_t avlbl_cids; struct ulp_cid_info* cid_array; scalar_t__ cid_free; scalar_t__ cid_alloc; } ;
struct iscsi_endpoint {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ulp_supported; } ;
struct TYPE_5__ {size_t cxns_per_ctrl; } ;
struct beiscsi_hba {struct ulp_cid_info** cid_array_info; TYPE_4__ fw_config; TYPE_3__* phwi_ctrlr; TYPE_1__ params; struct ulp_cid_info* ep_array; void* conn_table; } ;
struct beiscsi_conn {int dummy; } ;
struct TYPE_7__ {TYPE_2__* wrb_context; } ;
struct TYPE_6__ {size_t ulp_num; struct ulp_cid_info cid; } ;

/* Variables and functions */
 size_t BEISCSI_GET_CID_COUNT (struct beiscsi_hba*,size_t) ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 size_t BEISCSI_ULP_COUNT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ulp_cid_info*) ; 
 struct ulp_cid_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (size_t,void*) ; 

__attribute__((used)) static int hba_setup_cid_tbls(struct beiscsi_hba *phba)
{
	int ret;
	uint16_t i, ulp_num;
	struct ulp_cid_info *ptr_cid_info = NULL;

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, (void *)&phba->fw_config.ulp_supported)) {
			ptr_cid_info = kzalloc(sizeof(struct ulp_cid_info),
					       GFP_KERNEL);

			if (!ptr_cid_info) {
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
					    "BM_%d : Failed to allocate memory"
					    "for ULP_CID_INFO for ULP : %d\n",
					    ulp_num);
				ret = -ENOMEM;
				goto free_memory;

			}

			/* Allocate memory for CID array */
			ptr_cid_info->cid_array =
				kcalloc(BEISCSI_GET_CID_COUNT(phba, ulp_num),
					sizeof(*ptr_cid_info->cid_array),
					GFP_KERNEL);
			if (!ptr_cid_info->cid_array) {
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
					    "BM_%d : Failed to allocate memory"
					    "for CID_ARRAY for ULP : %d\n",
					    ulp_num);
				kfree(ptr_cid_info);
				ptr_cid_info = NULL;
				ret = -ENOMEM;

				goto free_memory;
			}
			ptr_cid_info->avlbl_cids = BEISCSI_GET_CID_COUNT(
						   phba, ulp_num);

			/* Save the cid_info_array ptr */
			phba->cid_array_info[ulp_num] = ptr_cid_info;
		}
	}
	phba->ep_array = kcalloc(phba->params.cxns_per_ctrl,
				 sizeof(struct iscsi_endpoint *),
				 GFP_KERNEL);
	if (!phba->ep_array) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to allocate memory in "
			    "hba_setup_cid_tbls\n");
		ret = -ENOMEM;

		goto free_memory;
	}

	phba->conn_table = kcalloc(phba->params.cxns_per_ctrl,
				   sizeof(struct beiscsi_conn *),
				   GFP_KERNEL);
	if (!phba->conn_table) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Failed to allocate memory in"
			    "hba_setup_cid_tbls\n");

		kfree(phba->ep_array);
		phba->ep_array = NULL;
		ret = -ENOMEM;

		goto free_memory;
	}

	for (i = 0; i < phba->params.cxns_per_ctrl; i++) {
		ulp_num = phba->phwi_ctrlr->wrb_context[i].ulp_num;

		ptr_cid_info = phba->cid_array_info[ulp_num];
		ptr_cid_info->cid_array[ptr_cid_info->cid_alloc++] =
			phba->phwi_ctrlr->wrb_context[i].cid;

	}

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, (void *)&phba->fw_config.ulp_supported)) {
			ptr_cid_info = phba->cid_array_info[ulp_num];

			ptr_cid_info->cid_alloc = 0;
			ptr_cid_info->cid_free = 0;
		}
	}
	return 0;

free_memory:
	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, (void *)&phba->fw_config.ulp_supported)) {
			ptr_cid_info = phba->cid_array_info[ulp_num];

			if (ptr_cid_info) {
				kfree(ptr_cid_info->cid_array);
				kfree(ptr_cid_info);
				phba->cid_array_info[ulp_num] = NULL;
			}
		}
	}

	return ret;
}