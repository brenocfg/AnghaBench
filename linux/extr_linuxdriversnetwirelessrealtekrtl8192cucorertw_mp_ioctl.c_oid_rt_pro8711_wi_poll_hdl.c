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

NDIS_STATUS oid_rt_pro8711_wi_poll_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)( poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	struct mp_wiparam *pwi_param;

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(struct mp_wiparam))
		return NDIS_STATUS_INVALID_LENGTH;

	if (Adapter->mppriv.workparam.bcompleted == _FALSE)
		return NDIS_STATUS_NOT_ACCEPTED;

	pwi_param = (struct mp_wiparam *)poid_par_priv->information_buf;

	_rtw_memcpy(pwi_param, &Adapter->mppriv.workparam, sizeof(struct mp_wiparam));
	Adapter->mppriv.act_in_progress = _FALSE;
//	RT_TRACE(_module_mp_, _drv_info_, ("rf:%x\n", pwiparam->IoValue));
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

_func_exit_;

	return status;
#else
	return 0;
#endif
}