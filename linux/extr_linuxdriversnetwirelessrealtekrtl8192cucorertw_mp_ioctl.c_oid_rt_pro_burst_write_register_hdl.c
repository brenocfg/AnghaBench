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

NDIS_STATUS oid_rt_pro_burst_write_register_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	pBurst_RW_Reg	pBstRwReg;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_burst_write_register_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	pBstRwReg = (pBurst_RW_Reg)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);
	rtw_write_mem(padapter, pBstRwReg->offset, (u32)pBstRwReg->len, pBstRwReg->Data);
	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_info_, ("-oid_rt_pro_burst_write_register_hdl\n"));

_func_exit_;

	return status;
#else
	return 0;
#endif
}