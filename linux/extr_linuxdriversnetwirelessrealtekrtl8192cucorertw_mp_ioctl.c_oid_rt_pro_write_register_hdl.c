#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  TYPE_1__* pRW_Reg ;
struct TYPE_2__ {int offset; int width; int value; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
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
 int /*<<< orphan*/  rtw_write16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

NDIS_STATUS oid_rt_pro_write_register_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	pRW_Reg 	RegRWStruct;
	u32		offset, width, value;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_,
		 ("+oid_rt_pro_write_register_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	RegRWStruct = (pRW_Reg)poid_par_priv->information_buf;
	offset = RegRWStruct->offset;
	width = RegRWStruct->width;
	value = RegRWStruct->value;

	if (offset > 0xFFF)
		return NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, LOWER);

	switch (RegRWStruct->width)
	{
		case 1:
			if (value > 0xFF) {
				status = NDIS_STATUS_NOT_ACCEPTED;
				break;
			}
			rtw_write8(padapter, offset, (u8)value);
			break;
		case 2:
			if (value > 0xFFFF) {
				status = NDIS_STATUS_NOT_ACCEPTED;
				break;
			}
			rtw_write16(padapter, offset, (u16)value);
			break;
		case 4:
			rtw_write32(padapter, offset, value);
			break;
		default:
			status = NDIS_STATUS_NOT_ACCEPTED;
			break;
	}

	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_info_,
		 ("-oid_rt_pro_write_register_hdl: offset=0x%08X width=%d value=0x%X\n",
		  offset, width, value));

_func_exit_;

	return status;
}