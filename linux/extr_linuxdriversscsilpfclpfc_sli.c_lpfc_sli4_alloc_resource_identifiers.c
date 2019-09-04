#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int max_rpi; int rpi_base; int max_vpi; int vpi_base; int max_xri; int xri_base; int max_vfi; int vfi_base; scalar_t__ xri_used; } ;
struct TYPE_4__ {int next_rpi; int* rpi_bmask; int* rpi_ids; int* xri_bmask; int* xri_ids; int* vfi_bmask; int* vfi_ids; int /*<<< orphan*/  sli4_flags; TYPE_1__ max_cfg_param; scalar_t__ extents_in_use; int /*<<< orphan*/  rpi_hdrs_in_use; } ;
struct lpfc_hba {int* vpi_bmask; int* vpi_ids; TYPE_2__ sli4_hba; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_INIT ; 
 int LOG_MBOX ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_IDX_RSRC_RDY ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_RPI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_VFI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_VPI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_XRI ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  lpfc_idx_rsrc_rdy ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int lpfc_sli4_alloc_extent (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_sli4_chk_avail_extnt_rsrc (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_sli4_dealloc_extent (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_dealloc_resource_identifiers (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_remove_rpis (struct lpfc_hba*) ; 
 scalar_t__ unlikely (int) ; 

int
lpfc_sli4_alloc_resource_identifiers(struct lpfc_hba *phba)
{
	int i, rc, error = 0;
	uint16_t count, base;
	unsigned long longs;

	if (!phba->sli4_hba.rpi_hdrs_in_use)
		phba->sli4_hba.next_rpi = phba->sli4_hba.max_cfg_param.max_rpi;
	if (phba->sli4_hba.extents_in_use) {
		/*
		 * The port supports resource extents. The XRI, VPI, VFI, RPI
		 * resource extent count must be read and allocated before
		 * provisioning the resource id arrays.
		 */
		if (bf_get(lpfc_idx_rsrc_rdy, &phba->sli4_hba.sli4_flags) ==
		    LPFC_IDX_RSRC_RDY) {
			/*
			 * Extent-based resources are set - the driver could
			 * be in a port reset. Figure out if any corrective
			 * actions need to be taken.
			 */
			rc = lpfc_sli4_chk_avail_extnt_rsrc(phba,
						 LPFC_RSC_TYPE_FCOE_VFI);
			if (rc != 0)
				error++;
			rc = lpfc_sli4_chk_avail_extnt_rsrc(phba,
						 LPFC_RSC_TYPE_FCOE_VPI);
			if (rc != 0)
				error++;
			rc = lpfc_sli4_chk_avail_extnt_rsrc(phba,
						 LPFC_RSC_TYPE_FCOE_XRI);
			if (rc != 0)
				error++;
			rc = lpfc_sli4_chk_avail_extnt_rsrc(phba,
						 LPFC_RSC_TYPE_FCOE_RPI);
			if (rc != 0)
				error++;

			/*
			 * It's possible that the number of resources
			 * provided to this port instance changed between
			 * resets.  Detect this condition and reallocate
			 * resources.  Otherwise, there is no action.
			 */
			if (error) {
				lpfc_printf_log(phba, KERN_INFO,
						LOG_MBOX | LOG_INIT,
						"2931 Detected extent resource "
						"change.  Reallocating all "
						"extents.\n");
				rc = lpfc_sli4_dealloc_extent(phba,
						 LPFC_RSC_TYPE_FCOE_VFI);
				rc = lpfc_sli4_dealloc_extent(phba,
						 LPFC_RSC_TYPE_FCOE_VPI);
				rc = lpfc_sli4_dealloc_extent(phba,
						 LPFC_RSC_TYPE_FCOE_XRI);
				rc = lpfc_sli4_dealloc_extent(phba,
						 LPFC_RSC_TYPE_FCOE_RPI);
			} else
				return 0;
		}

		rc = lpfc_sli4_alloc_extent(phba, LPFC_RSC_TYPE_FCOE_VFI);
		if (unlikely(rc))
			goto err_exit;

		rc = lpfc_sli4_alloc_extent(phba, LPFC_RSC_TYPE_FCOE_VPI);
		if (unlikely(rc))
			goto err_exit;

		rc = lpfc_sli4_alloc_extent(phba, LPFC_RSC_TYPE_FCOE_RPI);
		if (unlikely(rc))
			goto err_exit;

		rc = lpfc_sli4_alloc_extent(phba, LPFC_RSC_TYPE_FCOE_XRI);
		if (unlikely(rc))
			goto err_exit;
		bf_set(lpfc_idx_rsrc_rdy, &phba->sli4_hba.sli4_flags,
		       LPFC_IDX_RSRC_RDY);
		return rc;
	} else {
		/*
		 * The port does not support resource extents.  The XRI, VPI,
		 * VFI, RPI resource ids were determined from READ_CONFIG.
		 * Just allocate the bitmasks and provision the resource id
		 * arrays.  If a port reset is active, the resources don't
		 * need any action - just exit.
		 */
		if (bf_get(lpfc_idx_rsrc_rdy, &phba->sli4_hba.sli4_flags) ==
		    LPFC_IDX_RSRC_RDY) {
			lpfc_sli4_dealloc_resource_identifiers(phba);
			lpfc_sli4_remove_rpis(phba);
		}
		/* RPIs. */
		count = phba->sli4_hba.max_cfg_param.max_rpi;
		if (count <= 0) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"3279 Invalid provisioning of "
					"rpi:%d\n", count);
			rc = -EINVAL;
			goto err_exit;
		}
		base = phba->sli4_hba.max_cfg_param.rpi_base;
		longs = (count + BITS_PER_LONG - 1) / BITS_PER_LONG;
		phba->sli4_hba.rpi_bmask = kcalloc(longs,
						   sizeof(unsigned long),
						   GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.rpi_bmask)) {
			rc = -ENOMEM;
			goto err_exit;
		}
		phba->sli4_hba.rpi_ids = kcalloc(count, sizeof(uint16_t),
						 GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.rpi_ids)) {
			rc = -ENOMEM;
			goto free_rpi_bmask;
		}

		for (i = 0; i < count; i++)
			phba->sli4_hba.rpi_ids[i] = base + i;

		/* VPIs. */
		count = phba->sli4_hba.max_cfg_param.max_vpi;
		if (count <= 0) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"3280 Invalid provisioning of "
					"vpi:%d\n", count);
			rc = -EINVAL;
			goto free_rpi_ids;
		}
		base = phba->sli4_hba.max_cfg_param.vpi_base;
		longs = (count + BITS_PER_LONG - 1) / BITS_PER_LONG;
		phba->vpi_bmask = kcalloc(longs, sizeof(unsigned long),
					  GFP_KERNEL);
		if (unlikely(!phba->vpi_bmask)) {
			rc = -ENOMEM;
			goto free_rpi_ids;
		}
		phba->vpi_ids = kcalloc(count, sizeof(uint16_t),
					GFP_KERNEL);
		if (unlikely(!phba->vpi_ids)) {
			rc = -ENOMEM;
			goto free_vpi_bmask;
		}

		for (i = 0; i < count; i++)
			phba->vpi_ids[i] = base + i;

		/* XRIs. */
		count = phba->sli4_hba.max_cfg_param.max_xri;
		if (count <= 0) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"3281 Invalid provisioning of "
					"xri:%d\n", count);
			rc = -EINVAL;
			goto free_vpi_ids;
		}
		base = phba->sli4_hba.max_cfg_param.xri_base;
		longs = (count + BITS_PER_LONG - 1) / BITS_PER_LONG;
		phba->sli4_hba.xri_bmask = kcalloc(longs,
						   sizeof(unsigned long),
						   GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.xri_bmask)) {
			rc = -ENOMEM;
			goto free_vpi_ids;
		}
		phba->sli4_hba.max_cfg_param.xri_used = 0;
		phba->sli4_hba.xri_ids = kcalloc(count, sizeof(uint16_t),
						 GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.xri_ids)) {
			rc = -ENOMEM;
			goto free_xri_bmask;
		}

		for (i = 0; i < count; i++)
			phba->sli4_hba.xri_ids[i] = base + i;

		/* VFIs. */
		count = phba->sli4_hba.max_cfg_param.max_vfi;
		if (count <= 0) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"3282 Invalid provisioning of "
					"vfi:%d\n", count);
			rc = -EINVAL;
			goto free_xri_ids;
		}
		base = phba->sli4_hba.max_cfg_param.vfi_base;
		longs = (count + BITS_PER_LONG - 1) / BITS_PER_LONG;
		phba->sli4_hba.vfi_bmask = kcalloc(longs,
						   sizeof(unsigned long),
						   GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.vfi_bmask)) {
			rc = -ENOMEM;
			goto free_xri_ids;
		}
		phba->sli4_hba.vfi_ids = kcalloc(count, sizeof(uint16_t),
						 GFP_KERNEL);
		if (unlikely(!phba->sli4_hba.vfi_ids)) {
			rc = -ENOMEM;
			goto free_vfi_bmask;
		}

		for (i = 0; i < count; i++)
			phba->sli4_hba.vfi_ids[i] = base + i;

		/*
		 * Mark all resources ready.  An HBA reset doesn't need
		 * to reset the initialization.
		 */
		bf_set(lpfc_idx_rsrc_rdy, &phba->sli4_hba.sli4_flags,
		       LPFC_IDX_RSRC_RDY);
		return 0;
	}

 free_vfi_bmask:
	kfree(phba->sli4_hba.vfi_bmask);
	phba->sli4_hba.vfi_bmask = NULL;
 free_xri_ids:
	kfree(phba->sli4_hba.xri_ids);
	phba->sli4_hba.xri_ids = NULL;
 free_xri_bmask:
	kfree(phba->sli4_hba.xri_bmask);
	phba->sli4_hba.xri_bmask = NULL;
 free_vpi_ids:
	kfree(phba->vpi_ids);
	phba->vpi_ids = NULL;
 free_vpi_bmask:
	kfree(phba->vpi_bmask);
	phba->vpi_bmask = NULL;
 free_rpi_ids:
	kfree(phba->sli4_hba.rpi_ids);
	phba->sli4_hba.rpi_ids = NULL;
 free_rpi_bmask:
	kfree(phba->sli4_hba.rpi_bmask);
	phba->sli4_hba.rpi_bmask = NULL;
 err_exit:
	return rc;
}