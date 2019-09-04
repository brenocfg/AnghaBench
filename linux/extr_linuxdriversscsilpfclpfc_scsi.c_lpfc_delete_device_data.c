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
struct lpfc_hba {int /*<<< orphan*/  device_data_mem_pool; int /*<<< orphan*/  cfg_fof; } ;
struct lpfc_device_data {int /*<<< orphan*/  listentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct lpfc_device_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
lpfc_delete_device_data(struct lpfc_hba *phba,
			struct lpfc_device_data *lun_info)
{

	if (unlikely(!phba) || !lun_info  ||
	    !(phba->cfg_fof))
		return;

	if (!list_empty(&lun_info->listentry))
		list_del(&lun_info->listentry);
	mempool_free(lun_info, phba->device_data_mem_pool);
	return;
}