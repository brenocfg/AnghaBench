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

__attribute__((used)) static int rtw_tdls(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);

	printk( "[%s] extra = %s\n", __FUNCTION__, extra );
	//	WFD Sigma will use the tdls enable command to let the driver know we want to test the tdls now!
	if ( _rtw_memcmp( extra, "wfdenable=", 10 ) )
	{
		wrqu->data.length -=10;
		rtw_wfd_tdls_enable( dev, info, wrqu, &extra[10] );
		return ret;
	}
	else if ( _rtw_memcmp( extra, "weaksec=", 8 ) )
	{
		wrqu->data.length -=8;
		rtw_tdls_weaksec( dev, info, wrqu, &extra[8] );
		return ret;
	}
	else if ( _rtw_memcmp( extra, "tdlsenable=", 11 ) )
	{
		wrqu->data.length -=11;
		rtw_tdls_enable( dev, info, wrqu, &extra[11] );
		return ret;
	}

	if( padapter->tdlsinfo.enable == 0 )
	{
		printk("tdls haven't enabled\n");
		return 0;
	}

	if ( _rtw_memcmp( extra, "setup=", 6 ) )
	{
		wrqu->data.length -=6;
		rtw_tdls_setup( dev, info, wrqu, &extra[6] );
	}
	else if (_rtw_memcmp( extra, "tear=", 5 ) )
	{
		wrqu->data.length -= 5;
		rtw_tdls_teardown( dev, info, wrqu, &extra[5] );
	}
	else if (_rtw_memcmp( extra, "dis=", 4 ) )
	{
		wrqu->data.length -= 4;
		rtw_tdls_discovery( dev, info, wrqu, &extra[4] );
	}
	else if (_rtw_memcmp( extra, "sw=", 3 ) )
	{
		wrqu->data.length -= 3;
		rtw_tdls_ch_switch( dev, info, wrqu, &extra[3] );
	}
	else if (_rtw_memcmp( extra, "swoff=", 6 ) )
	{
		wrqu->data.length -= 6;
		rtw_tdls_ch_switch_off( dev, info, wrqu, &extra[6] );
	}	
	else if (_rtw_memcmp( extra, "pson=", 5 ) )
	{
		wrqu->data.length -= 5;
		rtw_tdls_pson( dev, info, wrqu, &extra[5] );
	}
	else if (_rtw_memcmp( extra, "psoff=", 6 ) )
	{
		wrqu->data.length -= 6;
		rtw_tdls_psoff( dev, info, wrqu, &extra[6] );
	}
#ifdef CONFIG_WFD
	else if (_rtw_memcmp( extra, "setip=", 6 ) )
	{
		wrqu->data.length -= 6;
		rtw_tdls_setip( dev, info, wrqu, &extra[6] );
	}
	else if (_rtw_memcmp( extra, "tprobe=", 6 ) )
	{
		issue_tunneled_probe_req((_adapter *)rtw_netdev_priv(dev));
	}
#endif //CONFIG_WFD

#endif //CONFIG_TDLS
	
	return ret;
}