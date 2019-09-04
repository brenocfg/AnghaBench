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

NDIS_STATUS oid_rt_pro8711_join_bss_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	PNDIS_802_11_SSID pssid;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_needed = (u32)sizeof(NDIS_802_11_SSID);
	*poid_par_priv->bytes_rw = 0;
	if (poid_par_priv->information_buf_len < *poid_par_priv->bytes_needed)
		return NDIS_STATUS_INVALID_LENGTH;

	pssid = (PNDIS_802_11_SSID)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);

	if (mp_start_joinbss(Adapter, pssid) == _FAIL)
		status = NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, RAISE);

	*poid_par_priv->bytes_rw = sizeof(NDIS_802_11_SSID);

_func_exit_;

	return status;
#else
	return 0;
#endif
}