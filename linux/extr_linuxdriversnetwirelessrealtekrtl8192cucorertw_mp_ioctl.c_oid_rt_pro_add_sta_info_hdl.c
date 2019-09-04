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

NDIS_STATUS oid_rt_pro_add_sta_info_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	struct sta_info *psta = NULL;
	UCHAR 		*macaddr;


	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_needed = ETH_ALEN;
	if (poid_par_priv->information_buf_len < *poid_par_priv->bytes_needed)
		return NDIS_STATUS_INVALID_LENGTH;

	macaddr = (UCHAR *) poid_par_priv->information_buf ;

	RT_TRACE(_module_rtl871x_ioctl_c_,_drv_notice_,
		 ("OID_RT_PRO_ADD_STA_INFO: addr="MAC_FMT"\n", MAC_ARG(macaddr) ));

	_irqlevel_changed_(&oldirql, LOWER);

	psta = rtw_get_stainfo(&Adapter->stapriv, macaddr);

	if (psta == NULL) { // the sta have been in sta_info_queue => do nothing
		psta = rtw_alloc_stainfo(&Adapter->stapriv, macaddr);

		if (psta == NULL) {
			RT_TRACE(_module_rtl871x_ioctl_c_,_drv_err_,("Can't alloc sta_info when OID_RT_PRO_ADD_STA_INFO\n"));
			status = NDIS_STATUS_FAILURE;
		}
	} else { //(between drv has received this event before and  fw have not yet to set key to CAM_ENTRY)
		RT_TRACE(_module_rtl871x_ioctl_c_, _drv_err_,
			("Error: OID_RT_PRO_ADD_STA_INFO: sta has been in sta_hash_queue \n"));
	}

	_irqlevel_changed_(&oldirql, RAISE);

	return status;
#else
	return 0;
#endif
}