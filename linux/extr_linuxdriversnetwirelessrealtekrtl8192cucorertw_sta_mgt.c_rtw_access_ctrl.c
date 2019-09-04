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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUE ; 

u8 rtw_access_ctrl(_adapter *padapter, u8 *mac_addr)
{
	u8 res = _TRUE;
#ifdef  CONFIG_AP_MODE
	_irqL irqL;
	_list	*plist, *phead;
	struct rtw_wlan_acl_node *paclnode;
	u8 match = _FALSE;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	_queue	*pacl_node_q =&pacl_list->acl_node_q;
	
	_enter_critical_bh(&(pacl_node_q->lock), &irqL);
	phead = get_list_head(pacl_node_q);
	plist = get_next(phead);		
	while ((rtw_end_of_queue_search(phead, plist)) == _FALSE)
	{
		paclnode = LIST_CONTAINOR(plist, struct rtw_wlan_acl_node, list);
		plist = get_next(plist);

		if(_rtw_memcmp(paclnode->addr, mac_addr, ETH_ALEN))
		{
			if(paclnode->valid == _TRUE)
			{
				match = _TRUE;
				break;
			}
		}		
	}	
	_exit_critical_bh(&(pacl_node_q->lock), &irqL);
	

	if(pacl_list->mode == 1)//accept unless in deny list
	{
		res = (match == _TRUE) ?  _FALSE:_TRUE;
	}	
	else if(pacl_list->mode == 2)//deny unless in accept list
	{
		res = (match == _TRUE) ?  _TRUE:_FALSE;
	}
	else
	{
		 res = _TRUE;
	}		
	
#endif

	return res;

}