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
typedef  int /*<<< orphan*/  u8 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_set_power_down_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u8		bpwrup;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
#ifdef PLATFORM_LINUX
#ifdef CONFIG_SDIO_HCI
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);
#endif
#endif

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID) {
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}

	RT_TRACE(_module_mp_, _drv_info_,
		 ("\n ===> Setoid_rt_set_power_down_hdl.\n"));

	_irqlevel_changed_(&oldirql, LOWER);

	bpwrup = *(u8 *)poid_par_priv->information_buf;
	//CALL  the power_down function
#ifdef PLATFORM_LINUX
#ifdef CONFIG_SDIO_HCI
	dev_power_down(padapter,bpwrup);
#endif
#endif
	_irqlevel_changed_(&oldirql, RAISE);

	//DEBUG_ERR(("\n <=== Query OID_RT_PRO_READ_REGISTER.
	//	Add:0x%08x Width:%d Value:0x%08x\n",RegRWStruct->offset,RegRWStruct->width,RegRWStruct->value));

_func_exit_;

	return status;
}