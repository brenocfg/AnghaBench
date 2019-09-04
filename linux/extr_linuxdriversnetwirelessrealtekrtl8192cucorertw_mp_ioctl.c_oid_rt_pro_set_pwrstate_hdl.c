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

NDIS_STATUS oid_rt_pro_set_pwrstate_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	uint pwr_mode, smart_ps;

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+Set OID_RT_PRO_SET_PWRSTATE\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_rw = 0;
	*poid_par_priv->bytes_needed = 8;

	if (poid_par_priv->information_buf_len < 8)
		return NDIS_STATUS_INVALID_LENGTH;

	pwr_mode = *(uint *)(poid_par_priv->information_buf);
	smart_ps = *(uint *)((int)poid_par_priv->information_buf + 4);

	*poid_par_priv->bytes_rw = 8;

_func_exit_;

	return status;
#else
	return 0;
#endif
}