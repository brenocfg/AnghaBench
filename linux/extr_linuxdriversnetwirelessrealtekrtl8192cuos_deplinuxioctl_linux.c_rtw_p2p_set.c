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

__attribute__((used)) static int rtw_p2p_set(struct net_device *dev,
                               struct iw_request_info *info,
                               union iwreq_data *wrqu, char *extra)
{
	
	int ret = 0;
#ifdef CONFIG_P2P

	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);	
	struct iw_point *pdata = &wrqu->data;
	struct wifidirect_info *pwdinfo= &(padapter->wdinfo);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;

	DBG_871X( "[%s] extra = %s\n", __FUNCTION__, extra );

	if ( _rtw_memcmp( extra, "enable=", 7 ) )
	{
		rtw_wext_p2p_enable( dev, info, wrqu, &extra[7] );
	}
	else if ( _rtw_memcmp( extra, "setDN=", 6 ) )
	{
		wrqu->data.length -= 6;
		rtw_p2p_setDN( dev, info, wrqu, &extra[6] );
	}
	else if ( _rtw_memcmp( extra, "profilefound=", 13 ) )
	{
		wrqu->data.length -= 13;
		rtw_p2p_profilefound( dev, info, wrqu, &extra[13] );
	}
	else if ( _rtw_memcmp( extra, "prov_disc=", 10 ) )
	{
		wrqu->data.length -= 10;
		rtw_p2p_prov_disc( dev, info, wrqu, &extra[10] );
	}
	else if ( _rtw_memcmp( extra, "nego=", 5 ) )
	{
		wrqu->data.length -= 5;
		rtw_p2p_connect( dev, info, wrqu, &extra[5] );
	}
	else if ( _rtw_memcmp( extra, "intent=", 7 ) )
	{
		//	Commented by Albert 2011/03/23
		//	The wrqu->data.length will include the null character
		//	So, we will decrease 7 + 1
		wrqu->data.length -= 8;
		rtw_p2p_set_intent( dev, info, wrqu, &extra[7] );
	}
	else if ( _rtw_memcmp( extra, "ssid=", 5 ) )
	{
		wrqu->data.length -= 5;
		rtw_p2p_set_go_nego_ssid( dev, info, wrqu, &extra[5] );
	}
	else if ( _rtw_memcmp( extra, "got_wpsinfo=", 12 ) )
	{
		wrqu->data.length -= 12;
		rtw_p2p_got_wpsinfo( dev, info, wrqu, &extra[12] );
	}
	else if ( _rtw_memcmp( extra, "listen_ch=", 10 ) )
	{
		//	Commented by Albert 2011/05/24
		//	The wrqu->data.length will include the null character
		//	So, we will decrease (10 + 1)	
		wrqu->data.length -= 11;
		rtw_p2p_set_listen_ch( dev, info, wrqu, &extra[10] );
	}
	else if ( _rtw_memcmp( extra, "op_ch=", 6 ) )
	{
		//	Commented by Albert 2011/05/24
		//	The wrqu->data.length will include the null character
		//	So, we will decrease (6 + 1)	
		wrqu->data.length -= 7;
		rtw_p2p_set_op_ch( dev, info, wrqu, &extra[6] );
	}
	else if ( _rtw_memcmp( extra, "invite=", 7 ) )
	{
		wrqu->data.length -= 8;
		rtw_p2p_invite_req( dev, info, wrqu, &extra[7] );
	}
	else if ( _rtw_memcmp( extra, "persistent=", 11 ) )
	{
		wrqu->data.length -= 11;
		rtw_p2p_set_persistent( dev, info, wrqu, &extra[11] );
	}
	else if ( _rtw_memcmp ( extra, "uuid=", 5) )
	{
		wrqu->data.length -= 5;
		ret = rtw_p2p_set_wps_uuid( dev, info, wrqu, &extra[5] );
	}
#ifdef CONFIG_WFD
	else if ( _rtw_memcmp( extra, "sa=", 3 ) )
	{
		//	sa: WFD Session Available information
		wrqu->data.length -= 3;
		rtw_p2p_set_sa( dev, info, wrqu, &extra[3] );
	}
	else if ( _rtw_memcmp( extra, "pc=", 3 ) )
	{
		//	pc: WFD Preferred Connection
		wrqu->data.length -= 3;
		rtw_p2p_set_pc( dev, info, wrqu, &extra[3] );
	}
	else if ( _rtw_memcmp( extra, "wfd_type=", 9 ) )
	{
		//	Specify this device is Mircast source or sink
		wrqu->data.length -= 9;
		rtw_p2p_set_wfd_device_type( dev, info, wrqu, &extra[9] );
	}
	else if ( _rtw_memcmp( extra, "scan_type=", 10 ) )
	{
		wrqu->data.length -= 10;
		rtw_p2p_set_scan_result_type( dev, info, wrqu, &extra[10] );
	}
	else if ( _rtw_memcmp( extra, "wfd_enable=", 11 ) )
	{
		wrqu->data.length -= 11;
		rtw_p2p_set_wfd_enable( dev, info, wrqu, &extra[11] );
	}
	else if ( _rtw_memcmp( extra, "driver_iface=", 13 ) )
	{
		wrqu->data.length -= 13;
		rtw_p2p_set_driver_iface( dev, info, wrqu, &extra[13] );
	}
#endif //CONFIG_WFD
#endif //CONFIG_P2P

	return ret;
		
}