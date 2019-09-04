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
typedef  int u32 ;
typedef  void* u16 ;
struct oid_par_priv {int information_buf_len; scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_4__ {int antenna_tx; int antenna_rx; } ;
struct TYPE_5__ {TYPE_1__ mppriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  SetAntenna (TYPE_2__*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_pro_set_antenna_bb_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u32		antenna;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_set_antenna_bb_hdl\n"));

	if (poid_par_priv->information_buf_len != sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	if (poid_par_priv->type_of_oid == SET_OID)
	{
		antenna = *(u32*)poid_par_priv->information_buf;

		Adapter->mppriv.antenna_tx = (u16)((antenna & 0xFFFF0000) >> 16);
		Adapter->mppriv.antenna_rx = (u16)(antenna & 0x0000FFFF);
		RT_TRACE(_module_mp_, _drv_notice_,
			 ("oid_rt_pro_set_antenna_bb_hdl: tx_ant=0x%04x rx_ant=0x%04x\n",
			  Adapter->mppriv.antenna_tx, Adapter->mppriv.antenna_rx));

		_irqlevel_changed_(&oldirql, LOWER);
		SetAntenna(Adapter);
		_irqlevel_changed_(&oldirql, RAISE);
	} else {
		antenna = (Adapter->mppriv.antenna_tx << 16)|Adapter->mppriv.antenna_rx;
		*(u32*)poid_par_priv->information_buf = antenna;
	}

_func_exit_;

	return status;
}