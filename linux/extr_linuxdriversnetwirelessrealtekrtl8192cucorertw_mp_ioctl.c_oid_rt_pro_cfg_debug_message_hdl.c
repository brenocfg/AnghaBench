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

NDIS_STATUS oid_rt_pro_cfg_debug_message_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	PCFG_DBG_MSG_STRUCT pdbg_msg;

_func_enter_;

//	RT_TRACE(0xffffffffff,_drv_alert_,("===> oid_rt_pro_cfg_debug_message_hdl.\n"));

#if 0//#ifdef CONFIG_DEBUG_RTL871X

	pdbg_msg = (PCFG_DBG_MSG_STRUCT)(poid_par_priv->information_buf);

	if (poid_par_priv->type_of_oid == SET_OID) {
		RT_TRACE(0xffffffffff, _drv_alert_,
			 ("===>Set level :0x%08x, H32:0x%08x L32:0x%08x\n",
			  pdbg_msg->DebugLevel, pdbg_msg->DebugComponent_H32, pdbg_msg->DebugComponent_L32));

		GlobalDebugLevel = pdbg_msg->DebugLevel;
		GlobalDebugComponents = (pdbg_msg->DebugComponent_H32 << 32) | pdbg_msg->DebugComponent_L32;
		RT_TRACE(0xffffffffff, _drv_alert_,
			 ("===> Set level :0x%08x, component:0x%016x\n",
			  GlobalDebugLevel, (u32)GlobalDebugComponents));
	} else {
		pdbg_msg->DebugLevel = GlobalDebugLevel;
		pdbg_msg->DebugComponent_H32 = (u32)(GlobalDebugComponents >> 32);
		pdbg_msg->DebugComponent_L32 = (u32)GlobalDebugComponents;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

		RT_TRACE(0xffffffffff, _drv_alert_,
			 ("===>Query level:0x%08x H32:0x%08x L32:0x%08x\n",
			  (u32)pdbg_msg->DebugLevel, (u32)pdbg_msg->DebugComponent_H32, (u32)pdbg_msg->DebugComponent_L32));
	}

#endif

_func_exit_;

	return status;
#else
	return 0;
#endif
}