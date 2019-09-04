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
struct wil_ring {int dummy; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  net_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wil_update_net_queues (struct wil6210_priv*,struct wil6210_vif*,struct wil_ring*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void wil_update_net_queues(struct wil6210_priv *wil, struct wil6210_vif *vif,
			   struct wil_ring *ring, bool check_stop)
{
	spin_lock(&wil->net_queue_lock);
	__wil_update_net_queues(wil, vif, ring, check_stop);
	spin_unlock(&wil->net_queue_lock);
}