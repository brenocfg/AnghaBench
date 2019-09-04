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

NDIS_STATUS oid_rt_get_power_mode_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);
//#ifdef PLATFORM_OS_XP
//	_irqL		oldirql;
//#endif

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID) {
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}
	if (poid_par_priv->information_buf_len < sizeof(u32)) {
		status = NDIS_STATUS_INVALID_LENGTH;
		return status;
	}

	RT_TRACE(_module_mp_, _drv_info_,
		 ("\n ===> oid_rt_get_power_mode_hdl.\n"));

//	_irqlevel_changed_(&oldirql, LOWER);
	*(int*)poid_par_priv->information_buf = Adapter->registrypriv.low_power ? POWER_LOW : POWER_NORMAL;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
//	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
#else
	return 0;
#endif
}