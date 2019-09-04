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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ efuse_GetCurrentSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_get_efuse_current_size_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u16 size;
	u8 ret;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len <sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	_irqlevel_changed_(&oldirql, LOWER);
	ret = efuse_GetCurrentSize(Adapter, &size);
	_irqlevel_changed_(&oldirql, RAISE);
	if (ret == _SUCCESS) {
		*(u32*)poid_par_priv->information_buf = size;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	} else
		status = NDIS_STATUS_FAILURE;

_func_exit_;

	return status;
}