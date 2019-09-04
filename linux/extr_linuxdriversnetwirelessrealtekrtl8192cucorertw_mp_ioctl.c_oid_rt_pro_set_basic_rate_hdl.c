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

NDIS_STATUS oid_rt_pro_set_basic_rate_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u32 ratevalue;
	u8 datarates[NumRates];
	int i;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_, ("+OID_RT_PRO_SET_BASIC_RATE\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;
#if 0
	ratevalue = *((u32*)poid_par_priv->information_buf);

	for (i = 0; i < NumRates; i++) {
		if (ratevalue == mpdatarate[i])
			datarates[i] = mpdatarate[i];
		else
			datarates[i] = 0xff;
		RT_TRACE(_module_rtl871x_ioctl_c_, _drv_info_, ("basicrate_inx=%d\n", datarates[i]));
	}

	_irqlevel_changed_(&oldirql, LOWER);

	if (rtw_setbasicrate_cmd(padapter, datarates) != _SUCCESS)
		status = NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, RAISE);
#endif
	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-OID_RT_PRO_SET_BASIC_RATE: status=0x%08X\n", status));

_func_exit_;

	return status;
#else
	return 0;
#endif
}