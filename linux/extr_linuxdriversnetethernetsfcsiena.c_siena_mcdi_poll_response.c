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
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_DWORD_0 ; 
 int EFX_DWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int FR_CZ_MC_TREG_SMEM ; 
 int /*<<< orphan*/  MCDI_HEADER_RESPONSE ; 
 unsigned int MCDI_PDU (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_readd (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool siena_mcdi_poll_response(struct efx_nic *efx)
{
	unsigned int pdu = FR_CZ_MC_TREG_SMEM + MCDI_PDU(efx);
	efx_dword_t hdr;

	efx_readd(efx, &hdr, pdu);

	/* All 1's indicates that shared memory is in reset (and is
	 * not a valid hdr). Wait for it to come out reset before
	 * completing the command
	 */
	return EFX_DWORD_FIELD(hdr, EFX_DWORD_0) != 0xffffffff &&
		EFX_DWORD_FIELD(hdr, MCDI_HEADER_RESPONSE);
}