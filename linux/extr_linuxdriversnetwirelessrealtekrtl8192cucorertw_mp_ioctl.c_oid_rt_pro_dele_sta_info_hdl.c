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

NDIS_STATUS oid_rt_pro_dele_sta_info_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	struct sta_info *psta = NULL;
	UCHAR		*macaddr;


	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_needed = ETH_ALEN;
	if (poid_par_priv->information_buf_len < *poid_par_priv->bytes_needed)
		return NDIS_STATUS_INVALID_LENGTH;

	macaddr = (UCHAR *) poid_par_priv->information_buf ;
	RT_TRACE(_module_rtl871x_ioctl_c_,_drv_notice_,
		 ("+OID_RT_PRO_ADD_STA_INFO: addr="MAC_FMT"\n", MAC_ARG(macaddr) ));

	psta = rtw_get_stainfo(&Adapter->stapriv, macaddr);
	if (psta != NULL) {
		_enter_critical(&(Adapter->stapriv.sta_hash_lock), &irqL);
		rtw_free_stainfo(Adapter, psta);
		_exit_critical(&(Adapter->stapriv.sta_hash_lock), &irqL);
	}

	return status;
#else
	return 0;
#endif
}