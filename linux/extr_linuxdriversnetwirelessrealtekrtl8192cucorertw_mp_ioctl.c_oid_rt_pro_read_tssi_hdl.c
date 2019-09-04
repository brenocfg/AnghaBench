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
struct oid_par_priv {int dummy; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */

NDIS_STATUS oid_rt_pro_read_tssi_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_read_tssi_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (Adapter->mppriv.act_in_progress == _TRUE)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u8))
		return NDIS_STATUS_INVALID_LENGTH;

	//init workparam
	Adapter->mppriv.act_in_progress = _TRUE;
	Adapter->mppriv.workparam.bcompleted = _FALSE;
	Adapter->mppriv.workparam.act_type = MPT_READ_TSSI;
	Adapter->mppriv.workparam.io_offset = 0;
	Adapter->mppriv.workparam.io_value = 0xFFFFFFFF;

	_irqlevel_changed_(&oldirql, LOWER);

	if (!rtw_gettssi_cmd(Adapter,0, (u8*)&Adapter->mppriv.workparam.io_value))
		status = NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
#else
	return 0;
#endif
}