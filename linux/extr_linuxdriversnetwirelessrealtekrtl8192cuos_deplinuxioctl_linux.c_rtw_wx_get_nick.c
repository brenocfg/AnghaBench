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
struct TYPE_2__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_memcpy (char*,char*,int) ; 

__attribute__((used)) static int rtw_wx_get_nick(struct net_device *dev, 
			     struct iw_request_info *info, 
			     union iwreq_data *wrqu, char *extra)
{	
	//_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	 //struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	 //struct security_priv *psecuritypriv = &padapter->securitypriv;

	if(extra)
	{
		wrqu->data.length = 14;
		wrqu->data.flags = 1;
		_rtw_memcpy(extra, "<WIFI@REALTEK>", 14);
	}

	//rtw_signal_process(pid, SIGUSR1); //for test

	//dump debug info here	
/*
	u32 dot11AuthAlgrthm;		// 802.11 auth, could be open, shared, and 8021x
	u32 dot11PrivacyAlgrthm;	// This specify the privacy for shared auth. algorithm.
	u32 dot118021XGrpPrivacy;	// This specify the privacy algthm. used for Grp key 
	u32 ndisauthtype;
	u32 ndisencryptstatus;
*/

	//DBG_871X("auth_alg=0x%x, enc_alg=0x%x, auth_type=0x%x, enc_type=0x%x\n", 
	//		psecuritypriv->dot11AuthAlgrthm, psecuritypriv->dot11PrivacyAlgrthm,
	//		psecuritypriv->ndisauthtype, psecuritypriv->ndisencryptstatus);
	
	//DBG_871X("enc_alg=0x%x\n", psecuritypriv->dot11PrivacyAlgrthm);
	//DBG_871X("auth_type=0x%x\n", psecuritypriv->ndisauthtype);
	//DBG_871X("enc_type=0x%x\n", psecuritypriv->ndisencryptstatus);

#if 0
	DBG_871X("dbg(0x210)=0x%x\n", rtw_read32(padapter, 0x210));
	DBG_871X("dbg(0x608)=0x%x\n", rtw_read32(padapter, 0x608));
	DBG_871X("dbg(0x280)=0x%x\n", rtw_read32(padapter, 0x280));
	DBG_871X("dbg(0x284)=0x%x\n", rtw_read32(padapter, 0x284));
	DBG_871X("dbg(0x288)=0x%x\n", rtw_read32(padapter, 0x288));
	
	DBG_871X("dbg(0x664)=0x%x\n", rtw_read32(padapter, 0x664));


	DBG_871X("\n");

	DBG_871X("dbg(0x430)=0x%x\n", rtw_read32(padapter, 0x430));
	DBG_871X("dbg(0x438)=0x%x\n", rtw_read32(padapter, 0x438));

	DBG_871X("dbg(0x440)=0x%x\n", rtw_read32(padapter, 0x440));
	
	DBG_871X("dbg(0x458)=0x%x\n", rtw_read32(padapter, 0x458));
	
	DBG_871X("dbg(0x484)=0x%x\n", rtw_read32(padapter, 0x484));
	DBG_871X("dbg(0x488)=0x%x\n", rtw_read32(padapter, 0x488));
	
	DBG_871X("dbg(0x444)=0x%x\n", rtw_read32(padapter, 0x444));
	DBG_871X("dbg(0x448)=0x%x\n", rtw_read32(padapter, 0x448));
	DBG_871X("dbg(0x44c)=0x%x\n", rtw_read32(padapter, 0x44c));
	DBG_871X("dbg(0x450)=0x%x\n", rtw_read32(padapter, 0x450));
#endif
	
	return 0;

}