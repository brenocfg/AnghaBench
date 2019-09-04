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

NDIS_STATUS oid_rt_pro_h2c_get_rate_table_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	#if 0
			struct mp_wi_cntx *pmp_wi_cntx=&(Adapter->mppriv.wi_cntx);
			u8 res=_SUCCESS;
			DEBUG_INFO(("===> Set OID_RT_PRO_H2C_GET_RATE_TABLE.\n"));

			if(pmp_wi_cntx->bmp_wi_progress ==_TRUE){
				DEBUG_ERR(("\n mp workitem is progressing, not allow to set another workitem right now!!!\n"));
				Status = NDIS_STATUS_NOT_ACCEPTED;
				break;
			}
			else{
				pmp_wi_cntx->bmp_wi_progress=_TRUE;
				pmp_wi_cntx->param.bcompleted=_FALSE;
				pmp_wi_cntx->param.act_type=MPT_GET_RATE_TABLE;
				pmp_wi_cntx->param.io_offset=0x0;
				pmp_wi_cntx->param.bytes_cnt=sizeof(struct getratable_rsp);
				pmp_wi_cntx->param.io_value=0xffffffff;

				res=rtw_getrttbl_cmd(Adapter,(struct getratable_rsp *)pmp_wi_cntx->param.data);
				*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
				if(res != _SUCCESS)
				{
					Status = NDIS_STATUS_NOT_ACCEPTED;
				}
			}
			DEBUG_INFO(("\n <=== Set OID_RT_PRO_H2C_GET_RATE_TABLE.\n"));
	#endif

_func_exit_;

	return status;
#else
	return 0;
#endif
}