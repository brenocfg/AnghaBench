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

__attribute__((used)) static int rtw_tdls_get(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_WFD

	DBG_871X( "[%s] extra = %s\n", __FUNCTION__, (char*) wrqu->data.pointer );

	if ( _rtw_memcmp( wrqu->data.pointer, "ip", 2 ) )
	{
		rtw_tdls_getip( dev, info, wrqu, extra );
	}
	if ( _rtw_memcmp( wrqu->data.pointer, "port", 4 ) )
	{
		rtw_tdls_getport( dev, info, wrqu, extra );
	}

	//WFDTDLS, for sigma test
	if ( _rtw_memcmp( wrqu->data.pointer, "dis", 3 ) )
	{
		rtw_tdls_dis_result( dev, info, wrqu, extra );
	}
	if ( _rtw_memcmp( wrqu->data.pointer, "status", 6 ) )
	{
		rtw_wfd_tdls_status( dev, info, wrqu, extra );
	}

#endif //CONFIG_WFD

	return ret;
}