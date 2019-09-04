#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {TYPE_2__* type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {scalar_t__ index; scalar_t__ entries; TYPE_1__ buf; } ;
struct efx_channel {int /*<<< orphan*/  channel; TYPE_3__ eventq; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  evq_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FFE_CZ_TIMER_MODE_DIS ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_SIZE ; 
 int /*<<< orphan*/  FRF_CZ_HOST_NOTIFY_MODE ; 
 int /*<<< orphan*/  FRF_CZ_TIMER_MODE ; 
 int /*<<< orphan*/  FRF_CZ_TIMER_Q_EN ; 
 int /*<<< orphan*/  FR_BZ_TIMER_TBL ; 
 int /*<<< orphan*/  __ffs (scalar_t__) ; 
 int /*<<< orphan*/  efx_init_special_buffer (struct efx_nic*,TYPE_3__*) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int efx_farch_ev_init(struct efx_channel *channel)
{
	efx_oword_t reg;
	struct efx_nic *efx = channel->efx;

	netif_dbg(efx, hw, efx->net_dev,
		  "channel %d event queue in special buffers %d-%d\n",
		  channel->channel, channel->eventq.index,
		  channel->eventq.index + channel->eventq.entries - 1);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL, channel->channel);

	/* Pin event queue buffer */
	efx_init_special_buffer(efx, &channel->eventq);

	/* Fill event queue with all ones (i.e. empty events) */
	memset(channel->eventq.buf.addr, 0xff, channel->eventq.buf.len);

	/* Push event queue to card */
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(channel->eventq.entries),
			     FRF_AZ_EVQ_BUF_BASE_ID, channel->eventq.index);
	efx_writeo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);

	return 0;
}