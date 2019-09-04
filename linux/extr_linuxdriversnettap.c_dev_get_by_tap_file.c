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
struct tap_dev {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct major_info {int /*<<< orphan*/  minor_lock; int /*<<< orphan*/  minor_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct tap_dev* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct major_info* tap_get_major (int) ; 

__attribute__((used)) static struct tap_dev *dev_get_by_tap_file(int major, int minor)
{
	struct net_device *dev = NULL;
	struct tap_dev *tap;
	struct major_info *tap_major;

	rcu_read_lock();
	tap_major = tap_get_major(major);
	if (!tap_major) {
		tap = NULL;
		goto unlock;
	}

	spin_lock(&tap_major->minor_lock);
	tap = idr_find(&tap_major->minor_idr, minor);
	if (tap) {
		dev = tap->dev;
		dev_hold(dev);
	}
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_read_unlock();
	return tap;
}