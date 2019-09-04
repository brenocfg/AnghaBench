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

NDIS_STATUS oid_rt_pro_read16_eeprom_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	pEEPROM_RWParam pEEPROM;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_, ("+Query OID_RT_PRO_READ16_EEPROM\n"));

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	pEEPROM = (pEEPROM_RWParam)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);
	pEEPROM->value = eeprom_read16(padapter, (u16)(pEEPROM->offset >> 1));
	_irqlevel_changed_(&oldirql, RAISE);

	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	RT_TRACE(_module_mp_,  _drv_notice_,
		 ("-Query OID_RT_PRO_READ16_EEPROM: offset=0x%x value=0x%x\n",
		  pEEPROM->offset, pEEPROM->value));

_func_exit_;

	return status;
#else
	return 0;
#endif
}