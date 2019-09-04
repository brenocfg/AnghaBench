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
typedef  int /*<<< orphan*/  u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; struct _adapter* adapter_context; } ;
struct eeprom_priv {int /*<<< orphan*/  channel_plan; } ;
struct _adapter {struct eeprom_priv eeprompriv; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 

uint oid_rt_get_channelplan_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *padapter = poid_par_priv->adapter_context;
	struct eeprom_priv *peeprompriv = &padapter->eeprompriv;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	*(u16 *)poid_par_priv->information_buf = peeprompriv->channel_plan;
	return RNDIS_STATUS_SUCCESS;
}