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
typedef  scalar_t__ u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_2__ {scalar_t__ start_addr; scalar_t__ cnts; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PEFUSE_ACCESS_STRUCT ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  EFUSE_ACCESS_STRUCT ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TYPE_AVAILABLE_EFUSE_BYTES_TOTAL ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 
 scalar_t__ rtw_efuse_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

NDIS_STATUS oid_rt_pro_read_efuse_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL oldirql;
#endif
	PEFUSE_ACCESS_STRUCT pefuse;
	u8 *data;
	u16 addr = 0, cnts = 0, max_available_size = 0;
	NDIS_STATUS status = NDIS_STATUS_SUCCESS;
	PADAPTER Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(EFUSE_ACCESS_STRUCT))
		return NDIS_STATUS_INVALID_LENGTH;

	pefuse = (PEFUSE_ACCESS_STRUCT)poid_par_priv->information_buf;
	addr = pefuse->start_addr;
	cnts = pefuse->cnts;
	data = pefuse->data;

	RT_TRACE(_module_mp_, _drv_notice_,
		("+oid_rt_pro_read_efuse_hd: buf_len=%ld addr=%d cnts=%d\n",
		 poid_par_priv->information_buf_len, addr, cnts));

	EFUSE_GetEfuseDefinition(Adapter, EFUSE_WIFI, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, (PVOID)&max_available_size, _FALSE);

	if ((addr + cnts) > max_available_size) {
		RT_TRACE(_module_mp_, _drv_err_, ("!oid_rt_pro_read_efuse_hdl: parameter error!\n"));
		return NDIS_STATUS_NOT_ACCEPTED;
	}

	_irqlevel_changed_(&oldirql, LOWER);
	if (rtw_efuse_access(Adapter, _FALSE, addr, cnts, data) == _FAIL) {
		RT_TRACE(_module_mp_, _drv_err_, ("!oid_rt_pro_read_efuse_hdl: rtw_efuse_access FAIL!\n"));
		status = NDIS_STATUS_FAILURE;
	} else
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
}