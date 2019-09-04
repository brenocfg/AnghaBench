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
typedef  int u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */

u8 rtw_access_ctrl(struct adapter *padapter, u8 *mac_addr)
{
	u8 res = true;
#ifdef CONFIG_88EU_AP_MODE
	struct list_head *plist, *phead;
	struct rtw_wlan_acl_node *paclnode;
	u8 match = false;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	struct __queue *pacl_node_q = &pacl_list->acl_node_q;

	spin_lock_bh(&pacl_node_q->lock);
	phead = get_list_head(pacl_node_q);
	plist = phead->next;
	while (phead != plist) {
		paclnode = container_of(plist, struct rtw_wlan_acl_node, list);
		plist = plist->next;

		if (!memcmp(paclnode->addr, mac_addr, ETH_ALEN)) {
			if (paclnode->valid) {
				match = true;
				break;
			}
		}
	}
	spin_unlock_bh(&pacl_node_q->lock);

	if (pacl_list->mode == 1)/* accept unless in deny list */
		res = (match) ? false : true;
	else if (pacl_list->mode == 2)/* deny unless in accept list */
		res = (match) ? true : false;
	else
		res = true;

#endif

	return res;
}