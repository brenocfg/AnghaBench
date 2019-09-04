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
struct TYPE_2__ {scalar_t__ major; scalar_t__ minor; scalar_t__ maint; scalar_t__ patch; scalar_t__ phase; scalar_t__ build; } ;
struct bfi_ioc_image_hdr_s {scalar_t__ signature; TYPE_1__ fwver; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  bfa_ioc_fwver_md5_check (struct bfi_ioc_image_hdr_s*,struct bfi_ioc_image_hdr_s*) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_fw_ver_compatible(struct bfi_ioc_image_hdr_s *drv_fwhdr,
				struct bfi_ioc_image_hdr_s *fwhdr_to_cmp)
{
	if (drv_fwhdr->signature != fwhdr_to_cmp->signature)
		return BFA_FALSE;

	if (drv_fwhdr->fwver.major != fwhdr_to_cmp->fwver.major)
		return BFA_FALSE;

	if (drv_fwhdr->fwver.minor != fwhdr_to_cmp->fwver.minor)
		return BFA_FALSE;

	if (drv_fwhdr->fwver.maint != fwhdr_to_cmp->fwver.maint)
		return BFA_FALSE;

	if (drv_fwhdr->fwver.patch == fwhdr_to_cmp->fwver.patch &&
		drv_fwhdr->fwver.phase == fwhdr_to_cmp->fwver.phase &&
		drv_fwhdr->fwver.build == fwhdr_to_cmp->fwver.build) {
		return bfa_ioc_fwver_md5_check(drv_fwhdr, fwhdr_to_cmp);
	}

	return BFA_TRUE;
}