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
typedef  int /*<<< orphan*/  u64 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; } ;
struct TYPE_4__ {TYPE_1__ recvpriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 

NDIS_STATUS oid_rt_get_total_rx_bytes_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);

	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}
	if(poid_par_priv->information_buf_len>= sizeof(ULONG))
	{
		//_rtw_memcpy(*(uint *)poid_par_priv->information_buf,padapter->recvpriv.rx_icv_err,sizeof(u32));
		*(u64 *)poid_par_priv->information_buf = padapter->recvpriv.rx_bytes;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	}
	else
	{
		status = NDIS_STATUS_INVALID_LENGTH ;
	}
	return status;
}