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
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 

__attribute__((used)) static bool
batadv_hardif_is_iface_up(const struct batadv_hard_iface *hard_iface)
{
	if (hard_iface->net_dev->flags & IFF_UP)
		return true;

	return false;
}