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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  r8712_SetContinuousTx (struct _adapter*,int /*<<< orphan*/ ) ; 

uint oid_rt_pro_set_continuous_tx_hdl(struct oid_par_priv
					     *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bStartTest;

	if (poid_par_priv->type_of_oid != SET_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	bStartTest = *((u32 *)poid_par_priv->information_buf);
	r8712_SetContinuousTx(Adapter, (u8)bStartTest);
	return RNDIS_STATUS_SUCCESS;
}