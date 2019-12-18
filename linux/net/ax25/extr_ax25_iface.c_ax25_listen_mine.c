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
struct listen_struct {struct net_device* dev; int /*<<< orphan*/  callsign; struct listen_struct* next; } ;
typedef  int /*<<< orphan*/  ax25_address ;

/* Variables and functions */
 scalar_t__ ax25cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct listen_struct* listen_list ; 
 int /*<<< orphan*/  listen_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ax25_listen_mine(ax25_address *callsign, struct net_device *dev)
{
	struct listen_struct *listen;

	spin_lock_bh(&listen_lock);
	for (listen = listen_list; listen != NULL; listen = listen->next)
		if (ax25cmp(&listen->callsign, callsign) == 0 &&
		    (listen->dev == dev || listen->dev == NULL)) {
			spin_unlock_bh(&listen_lock);
			return 1;
	}
	spin_unlock_bh(&listen_lock);

	return 0;
}