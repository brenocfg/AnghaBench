#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {scalar_t__ mp_mode; } ;
struct TYPE_7__ {TYPE_1__ mppriv; TYPE_2__ registrypriv; } ;
typedef  TYPE_3__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 scalar_t__ mp_start_test (TYPE_3__*) ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_pro_start_test_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u32		mode;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_start_test_hdl\n"));

	if (Adapter->registrypriv.mp_mode == 0)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	_irqlevel_changed_(&oldirql, LOWER);

	//IQCalibrateBcut(Adapter);

	mode = *((u32*)poid_par_priv->information_buf);
	Adapter->mppriv.mode = mode;// 1 for loopback

	if (mp_start_test(Adapter) == _FAIL) {
		status = NDIS_STATUS_NOT_ACCEPTED;
		goto exit;
	}

exit:
	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_notice_, ("-oid_rt_pro_start_test_hdl: mp_mode=%d\n", Adapter->mppriv.mode));

_func_exit_;

	return status;
}