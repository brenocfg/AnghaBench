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
struct net_device {int dummy; } ;
struct listen_struct {struct listen_struct* next; struct net_device* dev; int /*<<< orphan*/  callsign; } ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 scalar_t__ ax25cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct listen_struct*) ; 
 struct listen_struct* listen_list ; 
 int /*<<< orphan*/  listen_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_listen_release(ax25_address *callsign, struct net_device *dev)
{
	struct listen_struct *s, *listen;

	spin_lock_bh(&listen_lock);
	listen = listen_list;
	if (listen == NULL) {
		spin_unlock_bh(&listen_lock);
		return;
	}

	if (ax25cmp(&listen->callsign, callsign) == 0 && listen->dev == dev) {
		listen_list = listen->next;
		spin_unlock_bh(&listen_lock);
		kfree(listen);
		return;
	}

	while (listen != NULL && listen->next != NULL) {
		if (ax25cmp(&listen->next->callsign, callsign) == 0 && listen->next->dev == dev) {
			s = listen->next;
			listen->next = listen->next->next;
			spin_unlock_bh(&listen_lock);
			kfree(s);
			return;
		}

		listen = listen->next;
	}
	spin_unlock_bh(&listen_lock);
}