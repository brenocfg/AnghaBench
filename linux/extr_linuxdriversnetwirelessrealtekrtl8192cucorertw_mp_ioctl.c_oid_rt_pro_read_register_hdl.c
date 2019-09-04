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
typedef  int u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  TYPE_1__* pRW_Reg ;
struct TYPE_2__ {int offset; int width; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 
 int /*<<< orphan*/  rtw_read16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_read32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_read8 (int /*<<< orphan*/ ,int) ; 

NDIS_STATUS oid_rt_pro_read_register_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	pRW_Reg 	RegRWStruct;
	u32		offset, width;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_,
		 ("+oid_rt_pro_read_register_hdl\n"));

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	RegRWStruct = (pRW_Reg)poid_par_priv->information_buf;
	offset = RegRWStruct->offset;
	width = RegRWStruct->width;

	if (offset > 0xFFF)
		return NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, LOWER);

	switch (width) {
		case 1:
			RegRWStruct->value = rtw_read8(Adapter, offset);
			break;
		case 2:
			RegRWStruct->value = rtw_read16(Adapter, offset);
			break;
		default:
			width = 4;
			RegRWStruct->value = rtw_read32(Adapter, offset);
			break;
	}
	RT_TRACE(_module_mp_, _drv_notice_,
		 ("oid_rt_pro_read_register_hdl: offset:0x%04X value:0x%X\n",
		  offset, RegRWStruct->value));

	_irqlevel_changed_(&oldirql, RAISE);

	*poid_par_priv->bytes_rw = width;

_func_exit_;

	return status;
}