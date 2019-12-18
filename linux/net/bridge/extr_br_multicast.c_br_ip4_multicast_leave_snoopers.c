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
struct net_bridge {int /*<<< orphan*/  dev; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INADDR_ALLSNOOPERS_GROUP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __ip_mc_dec_group (struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct in_device* in_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 

__attribute__((used)) static void br_ip4_multicast_leave_snoopers(struct net_bridge *br)
{
	struct in_device *in_dev = in_dev_get(br->dev);

	if (WARN_ON(!in_dev))
		return;

	__ip_mc_dec_group(in_dev, htonl(INADDR_ALLSNOOPERS_GROUP), GFP_ATOMIC);
	in_dev_put(in_dev);
}