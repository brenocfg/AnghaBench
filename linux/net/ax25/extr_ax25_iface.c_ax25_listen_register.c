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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ ax25_listen_mine (int /*<<< orphan*/ *,struct net_device*) ; 
 struct listen_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct listen_struct* listen_list ; 
 int /*<<< orphan*/  listen_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ax25_listen_register(ax25_address *callsign, struct net_device *dev)
{
	struct listen_struct *listen;

	if (ax25_listen_mine(callsign, dev))
		return 0;

	if ((listen = kmalloc(sizeof(*listen), GFP_ATOMIC)) == NULL)
		return -ENOMEM;

	listen->callsign = *callsign;
	listen->dev      = dev;

	spin_lock_bh(&listen_lock);
	listen->next = listen_list;
	listen_list  = listen;
	spin_unlock_bh(&listen_lock);

	return 0;
}