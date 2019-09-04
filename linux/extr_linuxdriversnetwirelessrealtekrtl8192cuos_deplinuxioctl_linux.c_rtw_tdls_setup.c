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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rtw_tdls_setup(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS

	u8 i, j;
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	u8 mac_addr[ETH_ALEN];

#ifdef CONFIG_WFD
	struct wifidirect_info *pwdinfo= &(padapter->wdinfo);
#endif // CONFIG_WFD

	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length -1  );

	for( i=0, j=0 ; i < ETH_ALEN; i++, j+=3 ){
		mac_addr[i]=key_2char2num(*(extra+j), *(extra+j+1));
	}

#ifdef CONFIG_WFD
	if ( _AES_ != padapter->securitypriv.dot11PrivacyAlgrthm )
	{
		//	Weak Security situation with AP.
		if ( 0 == pwdinfo->wfd_tdls_weaksec )
		{
			//	Can't send the tdls setup request out!!
			DBG_871X( "[%s] Current link is not AES, SKIP sending the tdls setup request!!\n", __FUNCTION__ );
		}
		else
		{
			issue_tdls_setup_req(padapter, mac_addr);
		}
	}
	else
#endif // CONFIG_WFD
	{
		issue_tdls_setup_req(padapter, mac_addr);
	}
#endif
	
	return ret;
}