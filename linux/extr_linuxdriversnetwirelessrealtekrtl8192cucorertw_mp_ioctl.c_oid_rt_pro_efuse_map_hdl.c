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
typedef  scalar_t__ u16 ;
struct oid_par_priv {scalar_t__ information_buf_len; scalar_t__ type_of_oid; scalar_t__* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TYPE_EFUSE_MAP_LEN ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 
 scalar_t__ rtw_efuse_map_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_efuse_map_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

NDIS_STATUS oid_rt_pro_efuse_map_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u8		*data;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);
	u16	mapLen=0;

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_efuse_map_hdl\n"));

	EFUSE_GetEfuseDefinition(Adapter, EFUSE_WIFI, TYPE_EFUSE_MAP_LEN, (PVOID)&mapLen, _FALSE);

	*poid_par_priv->bytes_rw = 0;

	if (poid_par_priv->information_buf_len < mapLen)
		return NDIS_STATUS_INVALID_LENGTH;

	data = (u8*)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);

	if (poid_par_priv->type_of_oid == QUERY_OID)
	{
		RT_TRACE(_module_mp_, _drv_info_,
			("oid_rt_pro_efuse_map_hdl: READ\n"));

		if (rtw_efuse_map_read(Adapter, 0, mapLen, data) == _SUCCESS)
			*poid_par_priv->bytes_rw = mapLen;
		else {
			RT_TRACE(_module_mp_, _drv_err_,
				("oid_rt_pro_efuse_map_hdl: READ fail\n"));
			status = NDIS_STATUS_FAILURE;
		}
	} else {
		// SET_OID
		RT_TRACE(_module_mp_, _drv_info_,
			("oid_rt_pro_efuse_map_hdl: WRITE\n"));

		if (rtw_efuse_map_write(Adapter, 0, mapLen, data) == _SUCCESS)
			*poid_par_priv->bytes_rw = mapLen;
		else {
			RT_TRACE(_module_mp_, _drv_err_,
				("oid_rt_pro_efuse_map_hdl: WRITE fail\n"));
			status = NDIS_STATUS_FAILURE;
		}
	}

	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_info_,
		 ("-oid_rt_pro_efuse_map_hdl: status=0x%08X\n", status));

_func_exit_;

	return status;
}