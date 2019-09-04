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
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {unsigned int seqno; int resp_hdr_len; unsigned int resp_data_len; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  resprc; scalar_t__ credits; } ;
struct TYPE_2__ {int mcdi_max_ver; } ;

/* Variables and functions */
 unsigned int SEQ_MASK ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_complete_async (struct efx_mcdi_iface*,int) ; 
 int /*<<< orphan*/  efx_mcdi_complete_sync (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  efx_mcdi_errno (unsigned int) ; 
 int /*<<< orphan*/  efx_mcdi_read_response_header (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_mcdi_ev_cpl(struct efx_nic *efx, unsigned int seqno,
			    unsigned int datalen, unsigned int mcdi_err)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	bool wake = false;

	spin_lock(&mcdi->iface_lock);

	if ((seqno ^ mcdi->seqno) & SEQ_MASK) {
		if (mcdi->credits)
			/* The request has been cancelled */
			--mcdi->credits;
		else
			netif_err(efx, hw, efx->net_dev,
				  "MC response mismatch tx seq 0x%x rx "
				  "seq 0x%x\n", seqno, mcdi->seqno);
	} else {
		if (efx->type->mcdi_max_ver >= 2) {
			/* MCDI v2 responses don't fit in an event */
			efx_mcdi_read_response_header(efx);
		} else {
			mcdi->resprc = efx_mcdi_errno(mcdi_err);
			mcdi->resp_hdr_len = 4;
			mcdi->resp_data_len = datalen;
		}

		wake = true;
	}

	spin_unlock(&mcdi->iface_lock);

	if (wake) {
		if (!efx_mcdi_complete_async(mcdi, false))
			(void) efx_mcdi_complete_sync(mcdi);

		/* If the interface isn't RUNNING_ASYNC or
		 * RUNNING_SYNC then we've received a duplicate
		 * completion after we've already transitioned back to
		 * QUIESCENT. [A subsequent invocation would increment
		 * seqno, so would have failed the seqno check].
		 */
	}
}