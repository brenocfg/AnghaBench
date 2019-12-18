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
typedef  int /*<<< orphan*/  u16 ;
struct switchdev_notifier_fdb_info {unsigned char const* addr; int added_by_user; int offloaded; int /*<<< orphan*/  info; int /*<<< orphan*/  vid; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long SWITCHDEV_FDB_ADD_TO_DEVICE ; 
 unsigned long SWITCHDEV_FDB_DEL_TO_DEVICE ; 
 int /*<<< orphan*/  call_switchdev_notifiers (unsigned long,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
br_switchdev_fdb_call_notifiers(bool adding, const unsigned char *mac,
				u16 vid, struct net_device *dev,
				bool added_by_user, bool offloaded)
{
	struct switchdev_notifier_fdb_info info;
	unsigned long notifier_type;

	info.addr = mac;
	info.vid = vid;
	info.added_by_user = added_by_user;
	info.offloaded = offloaded;
	notifier_type = adding ? SWITCHDEV_FDB_ADD_TO_DEVICE : SWITCHDEV_FDB_DEL_TO_DEVICE;
	call_switchdev_notifiers(notifier_type, dev, &info.info, NULL);
}