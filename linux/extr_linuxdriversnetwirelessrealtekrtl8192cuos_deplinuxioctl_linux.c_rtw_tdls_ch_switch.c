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

__attribute__((used)) static int rtw_tdls_ch_switch(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
	
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct tdls_info	*ptdlsinfo = &padapter->tdlsinfo;
	u8 i, j, mac_addr[ETH_ALEN];
	struct sta_info *ptdls_sta = NULL;

	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length -1  );

	for( i=0, j=0 ; i < ETH_ALEN; i++, j+=3 ){
		mac_addr[i]=key_2char2num(*(extra+j), *(extra+j+1));
	}

	ptdls_sta = rtw_get_stainfo(&padapter->stapriv, mac_addr);
	if( ptdls_sta == NULL )
		return ret;
	ptdlsinfo->ch_sensing=1;

	rtw_tdls_cmd(padapter, ptdls_sta->hwaddr, TDLS_INIT_CH_SEN);

#endif //CONFIG_TDLS

		return ret;
}