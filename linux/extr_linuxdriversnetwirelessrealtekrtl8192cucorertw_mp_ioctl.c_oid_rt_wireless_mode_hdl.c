#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct oid_par_priv {int information_buf_len; scalar_t__ type_of_oid; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_3__ {int /*<<< orphan*/  wireless_mode; } ;
struct TYPE_4__ {TYPE_1__ registrypriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_mp_ ; 

NDIS_STATUS oid_rt_wireless_mode_hdl(struct oid_par_priv *poid_par_priv)
{
	NDIS_STATUS status = NDIS_STATUS_SUCCESS;
	PADAPTER Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	if (poid_par_priv->information_buf_len < sizeof(u8))
		return NDIS_STATUS_INVALID_LENGTH;

	if (poid_par_priv->type_of_oid == SET_OID) {
		Adapter->registrypriv.wireless_mode = *(u8*)poid_par_priv->information_buf;
	} else if (poid_par_priv->type_of_oid == QUERY_OID) {
		*(u8*)poid_par_priv->information_buf = Adapter->registrypriv.wireless_mode;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
		 RT_TRACE(_module_mp_, _drv_info_, ("-query Wireless Mode=%d\n", Adapter->registrypriv.wireless_mode));
	} else {
		status = NDIS_STATUS_NOT_ACCEPTED;
	}

_func_exit_;

	return status;
}