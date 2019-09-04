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
struct efx_special_buffer {unsigned int index; int entries; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FRF_AZ_BUF_CLR_CMD ; 
 int /*<<< orphan*/  FRF_AZ_BUF_CLR_END_ID ; 
 int /*<<< orphan*/  FRF_AZ_BUF_CLR_START_ID ; 
 int /*<<< orphan*/  FRF_AZ_BUF_UPD_CMD ; 
 int /*<<< orphan*/  FR_AZ_BUF_TBL_UPD ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
efx_fini_special_buffer(struct efx_nic *efx, struct efx_special_buffer *buffer)
{
	efx_oword_t buf_tbl_upd;
	unsigned int start = buffer->index;
	unsigned int end = (buffer->index + buffer->entries - 1);

	if (!buffer->entries)
		return;

	netif_dbg(efx, hw, efx->net_dev, "unmapping special buffers %d-%d\n",
		  buffer->index, buffer->index + buffer->entries - 1);

	EFX_POPULATE_OWORD_4(buf_tbl_upd,
			     FRF_AZ_BUF_UPD_CMD, 0,
			     FRF_AZ_BUF_CLR_CMD, 1,
			     FRF_AZ_BUF_CLR_END_ID, end,
			     FRF_AZ_BUF_CLR_START_ID, start);
	efx_writeo(efx, &buf_tbl_upd, FR_AZ_BUF_TBL_UPD);
}