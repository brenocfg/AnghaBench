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
typedef  unsigned int u32 ;
struct wlan_network {int fixed; int /*<<< orphan*/  list; scalar_t__ last_scanned; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  num_of_scanned; struct __queue free_bss_pool; } ;

/* Variables and functions */
 unsigned int SCANQUEUE_LIFETIME ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void _rtw_free_network(struct	mlme_priv *pmlmepriv, struct wlan_network *pnetwork, u8 isfreeall)
{
	unsigned int delta_time;
	u32 lifetime = SCANQUEUE_LIFETIME;
/* 	_irqL irqL; */
	struct __queue *free_queue = &(pmlmepriv->free_bss_pool);

	if (pnetwork == NULL)
		return;

	if (pnetwork->fixed == true)
		return;

	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true))
		lifetime = 1;

	if (!isfreeall) {
		delta_time = jiffies_to_msecs(jiffies - pnetwork->last_scanned);
		if (delta_time < lifetime)/*  unit:msec */
			return;
	}

	spin_lock_bh(&free_queue->lock);

	list_del_init(&(pnetwork->list));

	list_add_tail(&(pnetwork->list), &(free_queue->queue));

	pmlmepriv->num_of_scanned--;


	/* DBG_871X("_rtw_free_network:SSID =%s\n", pnetwork->network.Ssid.Ssid); */

	spin_unlock_bh(&free_queue->lock);
}