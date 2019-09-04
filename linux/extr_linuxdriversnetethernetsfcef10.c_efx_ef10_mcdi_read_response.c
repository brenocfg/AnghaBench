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
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; } ;
struct efx_ef10_nic_data {TYPE_1__ mcdi_buf; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void
efx_ef10_mcdi_read_response(struct efx_nic *efx, efx_dword_t *outbuf,
			    size_t offset, size_t outlen)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	const u8 *pdu = nic_data->mcdi_buf.addr;

	memcpy(outbuf, pdu + offset, outlen);
}