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

__attribute__((used)) static int rtw_tdls_enable(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS

	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct tdls_info	*ptdlsinfo = &padapter->tdlsinfo;
	_irqL	 irqL;
	_list	*plist, *phead;
	s32	index;
	struct sta_info *psta = NULL;
	struct	sta_priv *pstapriv = &padapter->stapriv;
	u8 tdls_sta[NUM_STA][ETH_ALEN];
	u8 empty_hwaddr[ETH_ALEN] = { 0x00 };

	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length -1  );

	_rtw_memset(tdls_sta, 0x00, sizeof(tdls_sta));

	if ( extra[ 0 ] == '0' )
	{
		ptdlsinfo->enable = 0;

		if(pstapriv->asoc_sta_count==1)
			return ret;

		_enter_critical_bh(&pstapriv->sta_hash_lock, &irqL);
		for(index=0; index< NUM_STA; index++)
		{
			phead = &(pstapriv->sta_hash[index]);
			plist = get_next(phead);
			
			while ((rtw_end_of_queue_search(phead, plist)) == _FALSE)
			{
				psta = LIST_CONTAINOR(plist, struct sta_info ,hash_list);

				plist = get_next(plist);

				if(psta->tdls_sta_state != TDLS_STATE_NONE)
				{
					_rtw_memcpy(tdls_sta[index], psta->hwaddr, ETH_ALEN);
				}
			}
		}
		_exit_critical_bh(&pstapriv->sta_hash_lock, &irqL);

		for(index=0; index< NUM_STA; index++)
		{
			if( !_rtw_memcmp(tdls_sta[index], empty_hwaddr, ETH_ALEN) )
			{
				printk("issue tear down to "MAC_FMT"\n", MAC_ARG(tdls_sta[index]));
				issue_tdls_teardown(padapter, tdls_sta[index]);
			}
		}
		rtw_tdls_cmd(padapter, myid(&(padapter->eeprompriv)), TDLS_RS_RCR);
		rtw_reset_tdls_info(padapter);
	}
	else if ( extra[ 0 ] == '1' )
	{
		ptdlsinfo->enable = 1;
	}
#endif //CONFIG_TDLS
	
	return ret;
}