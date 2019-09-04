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
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__ preamble; } ;
struct TYPE_4__ {TYPE_1__ registrypriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ PREAMBLE_AUTO ; 
 scalar_t__ PREAMBLE_LONG ; 
 scalar_t__ PREAMBLE_SHORT ; 
 scalar_t__ QUERY_OID ; 

NDIS_STATUS oid_rt_get_preamble_mode_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS	 	status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);
	ULONG			preamblemode = 0 ;			
		
	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		
	if(poid_par_priv->information_buf_len>= sizeof(ULONG))
	{		
		if(padapter->registrypriv.preamble == PREAMBLE_LONG)
			preamblemode = 0;
		else if (padapter->registrypriv.preamble == PREAMBLE_AUTO)
			preamblemode = 1;
		else if (padapter->registrypriv.preamble == PREAMBLE_SHORT)
			preamblemode = 2;
		
			
		*(ULONG *)poid_par_priv->information_buf = preamblemode ;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	}
	else
	{
		status = NDIS_STATUS_INVALID_LENGTH ;
	}
	return status;
}