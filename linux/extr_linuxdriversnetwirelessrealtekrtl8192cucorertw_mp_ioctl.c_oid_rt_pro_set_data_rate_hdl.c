#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_4__ {scalar_t__ rateidx; } ;
struct TYPE_5__ {TYPE_1__ mppriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 scalar_t__ MPT_RATE_LAST ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_DATA ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  SetDataRate (TYPE_2__*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_pro_set_data_rate_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u32		ratevalue;//4
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("+oid_rt_pro_set_data_rate_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len != sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	ratevalue = *((u32*)poid_par_priv->information_buf);//4
	RT_TRACE(_module_mp_, _drv_notice_,
		 ("oid_rt_pro_set_data_rate_hdl: data rate idx=%d\n", ratevalue));
	if (ratevalue >= MPT_RATE_LAST)
		return NDIS_STATUS_INVALID_DATA;

	Adapter->mppriv.rateidx = ratevalue;

	_irqlevel_changed_(&oldirql, LOWER);
	SetDataRate(Adapter);
	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
}