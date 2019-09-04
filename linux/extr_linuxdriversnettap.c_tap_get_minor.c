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
struct tap_dev {int minor; int /*<<< orphan*/  dev; } ;
struct major_info {int /*<<< orphan*/  minor_lock; int /*<<< orphan*/  minor_idr; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAP_NUM_DEVS ; 
 int idr_alloc (int /*<<< orphan*/ *,struct tap_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct major_info* tap_get_major (int /*<<< orphan*/ ) ; 

int tap_get_minor(dev_t major, struct tap_dev *tap)
{
	int retval = -ENOMEM;
	struct major_info *tap_major;

	rcu_read_lock();
	tap_major = tap_get_major(MAJOR(major));
	if (!tap_major) {
		retval = -EINVAL;
		goto unlock;
	}

	spin_lock(&tap_major->minor_lock);
	retval = idr_alloc(&tap_major->minor_idr, tap, 1, TAP_NUM_DEVS, GFP_ATOMIC);
	if (retval >= 0) {
		tap->minor = retval;
	} else if (retval == -ENOSPC) {
		netdev_err(tap->dev, "Too many tap devices\n");
		retval = -EINVAL;
	}
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_read_unlock();
	return retval < 0 ? retval : 0;
}