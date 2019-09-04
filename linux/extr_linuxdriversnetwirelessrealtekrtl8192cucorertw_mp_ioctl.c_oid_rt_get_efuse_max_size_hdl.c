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
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  efuse_GetMaxSize (int /*<<< orphan*/ ) ; 

NDIS_STATUS oid_rt_get_efuse_max_size_hdl(struct oid_par_priv *poid_par_priv)
{
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	*(u32*)poid_par_priv->information_buf = efuse_GetMaxSize(Adapter);
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	RT_TRACE(_module_mp_, _drv_info_,
		 ("-oid_rt_get_efuse_max_size_hdl: size=%d status=0x%08X\n",
		  *(int*)poid_par_priv->information_buf, status));

_func_exit_;

	return status;
}