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

NDIS_STATUS oid_rt_pro_query_dr_variable_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER		Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL			oldirql;
#endif
	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;

	DR_VARIABLE_STRUCT	*pdrv_var;


	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	*poid_par_priv->bytes_needed = sizeof(DR_VARIABLE_STRUCT);
	if (poid_par_priv->information_buf_len < *poid_par_priv->bytes_needed)
		return NDIS_STATUS_INVALID_LENGTH;

	RT_TRACE(_module_mp_, _drv_notice_, ("+Query Information, OID_RT_PRO_QUERY_DR_VARIABLE\n"));

	pdrv_var = (struct _DR_VARIABLE_STRUCT_ *)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);
	pdrv_var->variable = mp_query_drv_var(Adapter, pdrv_var->offset, pdrv_var->variable);
	_irqlevel_changed_(&oldirql, RAISE);

	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-oid_rt_pro_query_dr_variable_hdl: offset=0x%x valule=0x%x\n",
		  pdrv_var->offset, pdrv_var->variable));

	return status;
#else
	return 0;
#endif
}