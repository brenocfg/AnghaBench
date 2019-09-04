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
struct efx_nic {scalar_t__ mc_bist_for_other_fn; } ;
struct efx_mcdi_iface {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int ENETDOWN ; 
 scalar_t__ MCDI_MODE_FAIL ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_acquire_sync (struct efx_mcdi_iface*) ; 
 int efx_mcdi_check_supported (struct efx_nic*,unsigned int,size_t) ; 
 int /*<<< orphan*/  efx_mcdi_send_request (struct efx_nic*,unsigned int,int /*<<< orphan*/  const*,size_t) ; 

int efx_mcdi_rpc_start(struct efx_nic *efx, unsigned cmd,
		       const efx_dword_t *inbuf, size_t inlen)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	int rc;

	rc = efx_mcdi_check_supported(efx, cmd, inlen);
	if (rc)
		return rc;

	if (efx->mc_bist_for_other_fn)
		return -ENETDOWN;

	if (mcdi->mode == MCDI_MODE_FAIL)
		return -ENETDOWN;

	efx_mcdi_acquire_sync(mcdi);
	efx_mcdi_send_request(efx, cmd, inbuf, inlen);
	return 0;
}