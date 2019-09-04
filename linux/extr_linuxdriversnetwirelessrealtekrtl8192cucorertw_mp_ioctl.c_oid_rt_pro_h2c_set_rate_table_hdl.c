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

NDIS_STATUS oid_rt_pro_h2c_set_rate_table_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	struct setratable_parm *prate_table;
	u8		res;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_needed  = sizeof(struct setratable_parm);
	if (poid_par_priv->information_buf_len < sizeof(struct setratable_parm))
		return NDIS_STATUS_INVALID_LENGTH;

	prate_table = (struct setratable_parm*)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);
	res = rtw_setrttbl_cmd(Adapter, prate_table);
	_irqlevel_changed_(&oldirql, RAISE);

	if (res == _FAIL)
		status = NDIS_STATUS_FAILURE;

_func_exit_;

	return status;
#else
	return 0;
#endif
}