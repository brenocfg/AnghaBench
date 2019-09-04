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

NDIS_STATUS oid_rt_pro_set_pkt_test_mode_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER		Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;

	struct mlme_priv	*pmlmepriv = &Adapter->mlmepriv;
	struct mp_priv		*pmppriv = &Adapter->mppriv;
	u32 			type;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len <sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	type = *(u32*)poid_par_priv->information_buf;

	if (_LOOPBOOK_MODE_ == type) {
		pmppriv->mode = type;
		set_fwstate(pmlmepriv, WIFI_MP_LPBK_STATE); //append txdesc
		RT_TRACE(_module_mp_, _drv_info_, ("test mode change to loopback mode:0x%08x.\n", get_fwstate(pmlmepriv)));
	} else if (_2MAC_MODE_ == type){
		pmppriv->mode = type;
		_clr_fwstate_(pmlmepriv, WIFI_MP_LPBK_STATE);
		RT_TRACE(_module_mp_, _drv_info_, ("test mode change to 2mac mode:0x%08x.\n", get_fwstate(pmlmepriv)));
	} else
		status = NDIS_STATUS_NOT_ACCEPTED;

_func_exit_;

	return status;
#else
	return 0;
#endif
}