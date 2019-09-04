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
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 

NDIS_STATUS oid_rt_set_crystal_cap_hdl(struct oid_par_priv *poid_par_priv)
{
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif

	u32		crystal_cap = 0;

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len <sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	crystal_cap = *((u32*)poid_par_priv->information_buf);//4
	if (crystal_cap > 0xf)
		return NDIS_STATUS_NOT_ACCEPTED;

	Adapter->mppriv.curr_crystalcap = crystal_cap;

	_irqlevel_changed_(&oldirql,LOWER);
	SetCrystalCap(Adapter);
	_irqlevel_changed_(&oldirql,RAISE);

_func_exit_;

#endif
	return status;
}