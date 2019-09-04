#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; int /*<<< orphan*/  adapter_context; } ;
struct eeprom_priv {int /*<<< orphan*/  channel_plan; } ;
struct TYPE_2__ {struct eeprom_priv eeprompriv; } ;
typedef  TYPE_1__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 

NDIS_STATUS oid_rt_get_channelplan_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS	 	status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);
	struct eeprom_priv*	peeprompriv = &padapter->eeprompriv;	

	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	*(u16 *)poid_par_priv->information_buf = peeprompriv->channel_plan ;

	return status;
}