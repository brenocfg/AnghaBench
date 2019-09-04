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
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_3__ {scalar_t__ tx_pktcount; } ;
struct TYPE_4__ {TYPE_1__ mppriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _drv_alert_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_mp_ ; 

NDIS_STATUS oid_rt_pro_reset_tx_packet_sent_hdl(struct oid_par_priv *poid_par_priv)
{
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	if (poid_par_priv->type_of_oid != SET_OID) {
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}

	RT_TRACE(_module_mp_, _drv_alert_, ("===> oid_rt_pro_reset_tx_packet_sent_hdl.\n"));
	Adapter->mppriv.tx_pktcount = 0;

_func_exit_;

	return status;
}