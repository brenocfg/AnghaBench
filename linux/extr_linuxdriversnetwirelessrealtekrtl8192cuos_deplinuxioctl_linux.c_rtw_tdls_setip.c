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

__attribute__((used)) static int rtw_tdls_setip(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
#ifdef CONFIG_WFD
	
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct tdls_info *ptdlsinfo = &padapter->tdlsinfo;
	struct wifi_display_info *pwfd_info = ptdlsinfo->wfd_info;
	u8 i=0, j=0, k=0, tag=0, ip[3] = { 0xff }, *ptr = extra;
	
	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length - 1  );


	while( i < 4 )
	{
		for( j=0; j < 4; j++)
		{
			if( *( extra + j + tag ) == '.' || *( extra + j + tag ) == '\0' )
			{
				if( j == 1 )
					pwfd_info->ip_address[i]=convert_ip_addr( '0', '0', *(extra+(j-1)+tag));
				if( j == 2 )
					pwfd_info->ip_address[i]=convert_ip_addr( '0', *(extra+(j-2)+tag), *(extra+(j-1)+tag));
				if( j == 3 )
					pwfd_info->ip_address[i]=convert_ip_addr( *(extra+(j-3)+tag), *(extra+(j-2)+tag), *(extra+(j-1)+tag));	

				tag += j + 1;
				break;
			}
		}
		i++;
	}

	printk( "[%s] Set IP = %u.%u.%u.%u \n", __FUNCTION__, 
		ptdlsinfo->wfd_info->ip_address[0], ptdlsinfo->wfd_info->ip_address[1],
		ptdlsinfo->wfd_info->ip_address[2], ptdlsinfo->wfd_info->ip_address[3]
	);

#endif //CONFIG_WFD	
#endif //CONFIG_TDLS

	return ret;
}