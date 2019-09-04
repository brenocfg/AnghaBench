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
struct oid_par_priv {scalar_t__ type_of_oid; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oid_rt_pro_read_efuse_hdl (struct oid_par_priv*) ; 
 int /*<<< orphan*/  oid_rt_pro_write_efuse_hdl (struct oid_par_priv*) ; 

NDIS_STATUS oid_rt_pro_efuse_hdl(struct oid_par_priv *poid_par_priv)
{
	NDIS_STATUS	status;

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_, ("+oid_rt_pro_efuse_hdl\n"));

	if (poid_par_priv->type_of_oid == QUERY_OID)
		status = oid_rt_pro_read_efuse_hdl(poid_par_priv);
	else
		status = oid_rt_pro_write_efuse_hdl(poid_par_priv);

	RT_TRACE(_module_mp_, _drv_info_, ("-oid_rt_pro_efuse_hdl: status=0x%08X\n", status));

_func_exit_;

	return status;
}