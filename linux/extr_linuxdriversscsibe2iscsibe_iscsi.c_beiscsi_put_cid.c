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
typedef  size_t uint16_t ;
struct ulp_cid_info {unsigned short* cid_array; size_t cid_free; int /*<<< orphan*/  avlbl_cids; } ;
struct hwi_wrb_context {size_t ulp_num; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct beiscsi_hba {struct ulp_cid_info** cid_array_info; struct hwi_controller* phwi_ctrlr; } ;

/* Variables and functions */
 size_t BEISCSI_GET_CID_COUNT (struct beiscsi_hba*,size_t) ; 
 size_t BE_GET_CRI_FROM_CID (unsigned short) ; 
 unsigned short BE_INVALID_CID ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,unsigned short,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void beiscsi_put_cid(struct beiscsi_hba *phba, unsigned short cid)
{
	uint16_t cri_index = BE_GET_CRI_FROM_CID(cid);
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	struct ulp_cid_info *cid_info;
	uint16_t cid_post_ulp;

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	cid_post_ulp = pwrb_context->ulp_num;

	cid_info = phba->cid_array_info[cid_post_ulp];
	/* fill only in empty slot */
	if (cid_info->cid_array[cid_info->cid_free] != BE_INVALID_CID) {
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : failed to put cid %u: available %u:%u\n",
			      cid, cid_info->avlbl_cids, cid_info->cid_free);
		return;
	}
	cid_info->cid_array[cid_info->cid_free++] = cid;
	if (cid_info->cid_free == BEISCSI_GET_CID_COUNT(phba, cid_post_ulp))
		cid_info->cid_free = 0;
	cid_info->avlbl_cids++;
}