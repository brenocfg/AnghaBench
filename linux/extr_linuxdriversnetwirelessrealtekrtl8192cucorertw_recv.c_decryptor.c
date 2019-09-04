#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int bdecrypted; int encrypt; int hdrlen; int key_index; } ;
struct TYPE_9__ {int* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct security_priv {int dot11PrivacyKeyIndex; int dot118021XGrpKeyid; scalar_t__ sw_decrypt; int busetkipkey; scalar_t__ hw_decrypted; } ;
struct TYPE_11__ {int /*<<< orphan*/  free_recv_queue; } ;
struct TYPE_12__ {TYPE_3__ recvpriv; struct security_priv securitypriv; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WEP_KEYS ; 
#define  _AES_ 131 
 scalar_t__ _FAIL ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _SUCCESS ; 
#define  _TKIP_ 130 
 scalar_t__ _TRUE ; 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ rtw_aes_decrypt (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_tkip_decrypt (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  rtw_wep_decrypt (TYPE_4__*,int*) ; 

union recv_frame * decryptor(_adapter *padapter,union recv_frame *precv_frame)
{

	struct rx_pkt_attrib *prxattrib = &precv_frame->u.hdr.attrib;
	struct security_priv *psecuritypriv=&padapter->securitypriv;
	union recv_frame *return_packet=precv_frame;
	u32	 res=_SUCCESS;
_func_enter_;

	RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("prxstat->decrypted=%x prxattrib->encrypt = 0x%03x\n",prxattrib->bdecrypted,prxattrib->encrypt));

	if(prxattrib->encrypt>0)
	{
		u8 *iv = precv_frame->u.hdr.rx_data+prxattrib->hdrlen;
		prxattrib->key_index = ( ((iv[3])>>6)&0x3) ;

		if(prxattrib->key_index > WEP_KEYS)
		{
			DBG_871X("prxattrib->key_index(%d) > WEP_KEYS \n", prxattrib->key_index);

			switch(prxattrib->encrypt){
				case _WEP40_:
				case _WEP104_:
					prxattrib->key_index = psecuritypriv->dot11PrivacyKeyIndex;
					break;
				case _TKIP_:			
				case _AES_:						
				default:
					prxattrib->key_index = psecuritypriv->dot118021XGrpKeyid;
					break;
			}	
		}			
	}

	if((prxattrib->encrypt>0) && ((prxattrib->bdecrypted==0) ||(psecuritypriv->sw_decrypt==_TRUE)))
	{

#ifdef CONFIG_CONCURRENT_MODE
		if(!IS_MCAST(prxattrib->ra))//bc/mc packets use sw decryption for concurrent mode
#endif			
		psecuritypriv->hw_decrypted=_FALSE;

		#ifdef DBG_RX_DECRYPTOR
		DBG_871X("prxstat->bdecrypted:%d,  prxattrib->encrypt:%d,  Setting psecuritypriv->hw_decrypted = %d\n"
			, prxattrib->bdecrypted ,prxattrib->encrypt, psecuritypriv->hw_decrypted);
		#endif

		switch(prxattrib->encrypt){
		case _WEP40_:
		case _WEP104_:
			rtw_wep_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _TKIP_:
			res = rtw_tkip_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _AES_:
			res = rtw_aes_decrypt(padapter, (u8 * )precv_frame);
			break;
		default:
				break;
		}
	}
	else if(prxattrib->bdecrypted==1
		&& prxattrib->encrypt >0
		&& (psecuritypriv->busetkipkey==1 || prxattrib->encrypt !=_TKIP_ )
		)
	{
#if 0
		if((prxstat->icv==1)&&(prxattrib->encrypt!=_AES_))
		{
			psecuritypriv->hw_decrypted=_FALSE;

			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("psecuritypriv->hw_decrypted=_FALSE"));

			rtw_free_recvframe(precv_frame, &padapter->recvpriv.free_recv_queue);

			return_packet=NULL;

		}
		else
#endif
		{
			psecuritypriv->hw_decrypted=_TRUE;
			#ifdef DBG_RX_DECRYPTOR
			DBG_871X("prxstat->bdecrypted:%d,  prxattrib->encrypt:%d,  Setting psecuritypriv->hw_decrypted = %d\n"
			, prxattrib->bdecrypted ,prxattrib->encrypt, psecuritypriv->hw_decrypted);
			#endif

		}
	}
	else {
		#ifdef DBG_RX_DECRYPTOR
		DBG_871X("prxstat->bdecrypted:%d,  prxattrib->encrypt:%d,  psecuritypriv->hw_decrypted:%d\n"
		, prxattrib->bdecrypted ,prxattrib->encrypt, psecuritypriv->hw_decrypted);
		#endif
	}
	
	if(res == _FAIL)
	{
		rtw_free_recvframe(return_packet,&padapter->recvpriv.free_recv_queue);			
		return_packet = NULL;
		
	}
	//recvframe_chkmic(adapter, precv_frame);   //move to recvframme_defrag function
	
_func_exit_;

	return return_packet;

}