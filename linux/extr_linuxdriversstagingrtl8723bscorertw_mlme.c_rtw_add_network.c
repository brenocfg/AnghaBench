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
struct wlan_bssid_ex {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_update_scanned_network (struct adapter*,struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  update_current_network (struct adapter*,struct wlan_bssid_ex*) ; 

void rtw_add_network(struct adapter *adapter, struct wlan_bssid_ex *pnetwork)
{
	/* struct __queue	*queue	= &(pmlmepriv->scanned_queue); */

	/* spin_lock_bh(&queue->lock); */

	update_current_network(adapter, pnetwork);

	rtw_update_scanned_network(adapter, pnetwork);

	/* spin_unlock_bh(&queue->lock); */
}