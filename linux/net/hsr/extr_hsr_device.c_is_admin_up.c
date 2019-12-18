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
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 

__attribute__((used)) static bool is_admin_up(struct net_device *dev)
{
	return dev && (dev->flags & IFF_UP);
}