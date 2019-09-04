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

NDIS_STATUS oid_rt_pro_write_txcmd_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	PADAPTER	Adapter = (PADAPTER)( poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif

	TX_CMD_Desc	*TxCmd_Info;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	RT_TRACE(_module_mp_, _drv_info_, ("+Set OID_RT_PRO_WRITE_TXCMD\n"));

	TxCmd_Info=(TX_CMD_Desc*)poid_par_priv->information_buf;

	RT_TRACE(_module_mp_, _drv_info_, ("WRITE_TXCMD:Addr=%.8X\n", TxCmd_Info->offset));
  	RT_TRACE(_module_mp_, _drv_info_, ("WRITE_TXCMD:1.)%.8X\n", (ULONG)TxCmd_Info->TxCMD.value[0]));
	RT_TRACE(_module_mp_, _drv_info_, ("WRITE_TXCMD:2.)%.8X\n", (ULONG)TxCmd_Info->TxCMD.value[1]));
	RT_TRACE(_module_mp_, _drv_info_, (("WRITE_TXCMD:3.)%.8X\n", (ULONG)TxCmd_Info->TxCMD.value[2]));
	RT_TRACE(_module_mp_, _drv_info_, ("WRITE_TXCMD:4.)%.8X\n", (ULONG)TxCmd_Info->TxCMD.value[3]));

	_irqlevel_changed_(&oldirql, LOWER);

	rtw_write32(Adapter, TxCmd_Info->offset + 0, (unsigned int)TxCmd_Info->TxCMD.value[0]);
	rtw_write32(Adapter, TxCmd_Info->offset + 4, (unsigned int)TxCmd_Info->TxCMD.value[1]);

	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-Set OID_RT_PRO_WRITE_TXCMD: status=0x%08X\n", status));

_func_exit_;

	return status;
#else
	return 0;
#endif
}