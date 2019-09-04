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

NDIS_STATUS oid_rt_pro_set_tx_agc_offset_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

	u32 		txagc;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	txagc = *(u32*)poid_par_priv->information_buf;
	RT_TRACE(_module_mp_, _drv_info_,
		 ("oid_rt_pro_set_tx_agc_offset_hdl: 0x%08x\n", txagc));

	_irqlevel_changed_(&oldirql, LOWER);
	SetTxAGCOffset(Adapter, txagc);
	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
#else
	return 0;
#endif
}