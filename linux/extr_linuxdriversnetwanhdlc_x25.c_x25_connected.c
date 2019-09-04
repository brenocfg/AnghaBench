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

/* Variables and functions */
 int /*<<< orphan*/  X25_IFACE_CONNECT ; 
 int /*<<< orphan*/  x25_connect_disconnect (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x25_connected(struct net_device *dev, int reason)
{
	x25_connect_disconnect(dev, reason, X25_IFACE_CONNECT);
}