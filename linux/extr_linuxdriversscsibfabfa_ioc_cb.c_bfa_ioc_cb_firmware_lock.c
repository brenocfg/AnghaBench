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
struct bfi_ioc_image_hdr_s {int dummy; } ;
struct bfa_ioc_s {int dummy; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int BFI_IOC_DISABLED ; 
 int BFI_IOC_UNINIT ; 
 int bfa_ioc_cb_get_alt_ioc_fwstate (struct bfa_ioc_s*) ; 
 int bfa_ioc_cb_get_cur_ioc_fwstate (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_cmp (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_get (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_cb_firmware_lock(struct bfa_ioc_s *ioc)
{
	enum bfi_ioc_state alt_fwstate, cur_fwstate;
	struct bfi_ioc_image_hdr_s fwhdr;

	cur_fwstate = bfa_ioc_cb_get_cur_ioc_fwstate(ioc);
	bfa_trc(ioc, cur_fwstate);
	alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate(ioc);
	bfa_trc(ioc, alt_fwstate);

	/*
	 * Uninit implies this is the only driver as of now.
	 */
	if (cur_fwstate == BFI_IOC_UNINIT)
		return BFA_TRUE;
	/*
	 * Check if another driver with a different firmware is active
	 */
	bfa_ioc_fwver_get(ioc, &fwhdr);
	if (!bfa_ioc_fwver_cmp(ioc, &fwhdr) &&
		alt_fwstate != BFI_IOC_DISABLED) {
		bfa_trc(ioc, alt_fwstate);
		return BFA_FALSE;
	}

	return BFA_TRUE;
}