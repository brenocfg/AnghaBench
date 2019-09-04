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
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 

NDIS_STATUS oid_rt_supported_wireless_mode_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS	 	status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);
	ULONG 			ulInfo = 0 ;
	//DEBUG_ERR(("<**********************oid_rt_supported_wireless_mode_hdl \n"));	
	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		
	if(poid_par_priv->information_buf_len >= sizeof(ULONG)){
		ulInfo |= 0x0100; //WIRELESS_MODE_B
		ulInfo |= 0x0200; //WIRELESS_MODE_G
		ulInfo |= 0x0400; //WIRELESS_MODE_A

		*(ULONG *) poid_par_priv->information_buf = ulInfo;		
		//DEBUG_ERR(("<===oid_rt_supported_wireless_mode %x\n",ulInfo));	
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	}
	else{
		status = NDIS_STATUS_INVALID_LENGTH;
	}		

	return status;
}