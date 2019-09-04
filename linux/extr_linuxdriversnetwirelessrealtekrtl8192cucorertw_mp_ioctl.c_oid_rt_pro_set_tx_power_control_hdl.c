#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_4__ {scalar_t__ txpoweridx; } ;
struct TYPE_5__ {TYPE_1__ mppriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 scalar_t__ MAX_TX_PWR_INDEX_N_MODE ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  SetTxPower (TYPE_2__*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_pro_set_tx_power_control_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u32		tx_pwr_idx;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_, ("+oid_rt_pro_set_tx_power_control_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len != sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	tx_pwr_idx = *((u32*)poid_par_priv->information_buf);
	if (tx_pwr_idx > MAX_TX_PWR_INDEX_N_MODE)
		return NDIS_STATUS_NOT_ACCEPTED;

	Adapter->mppriv.txpoweridx = (u8)tx_pwr_idx;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("oid_rt_pro_set_tx_power_control_hdl: idx=0x%2x\n",
		  Adapter->mppriv.txpoweridx));

	_irqlevel_changed_(&oldirql, LOWER);
	SetTxPower(Adapter);
	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
}