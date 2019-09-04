#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {int fixed; TYPE_1__ network; } ;
struct sta_priv {int asoc_sta_count; int /*<<< orphan*/  sta_hash_lock; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int /*<<< orphan*/  scanned_queue; struct wlan_network cur_network; } ;
struct _adapter {struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  free_network_nolock (struct mlme_priv*,struct wlan_network*) ; 
 struct wlan_network* r8712_find_network (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_free_all_stainfo (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_stainfo (struct _adapter*,struct sta_info*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_free_assoc_resources(struct _adapter *adapter)
{
	unsigned long irqL;
	struct wlan_network *pwlan = NULL;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct sta_priv *pstapriv = &adapter->stapriv;
	struct wlan_network *tgt_network = &pmlmepriv->cur_network;

	pwlan = r8712_find_network(&pmlmepriv->scanned_queue,
				   tgt_network->network.MacAddress);

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE)) {
		struct sta_info *psta;

		psta = r8712_get_stainfo(&adapter->stapriv,
					 tgt_network->network.MacAddress);

		spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
		r8712_free_stainfo(adapter,  psta);
		spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
	}

	if (check_fwstate(pmlmepriv,
	    WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE | WIFI_AP_STATE))
		r8712_free_all_stainfo(adapter);
	if (pwlan)
		pwlan->fixed = false;

	if (((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) &&
	     (adapter->stapriv.asoc_sta_count == 1)))
		free_network_nolock(pmlmepriv, pwlan);
}