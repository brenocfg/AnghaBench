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

NDIS_STATUS oid_rt_pro_qry_pwrstate_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < 8)
		return NDIS_STATUS_INVALID_LENGTH;

	*poid_par_priv->bytes_rw = 8;
	_rtw_memcpy(poid_par_priv->information_buf, &(Adapter->pwrctrlpriv.pwr_mode), 8);
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-oid_rt_pro_qry_pwrstate_hdl: pwr_mode=%d smart_ps=%d\n",
		  Adapter->pwrctrlpriv.pwr_mode, Adapter->pwrctrlpriv.smart_ps));

_func_exit_;

	return status;
#else
	return 0;
#endif
}