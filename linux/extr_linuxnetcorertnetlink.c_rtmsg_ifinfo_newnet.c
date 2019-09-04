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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  rtmsg_ifinfo_event (int,struct net_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtnl_get_event (int /*<<< orphan*/ ) ; 

void rtmsg_ifinfo_newnet(int type, struct net_device *dev, unsigned int change,
			 gfp_t flags, int *new_nsid, int new_ifindex)
{
	rtmsg_ifinfo_event(type, dev, change, rtnl_get_event(0), flags,
			   new_nsid, new_ifindex);
}