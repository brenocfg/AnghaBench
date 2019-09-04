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
struct tap_dev {int /*<<< orphan*/  minor; } ;
struct major_info {int /*<<< orphan*/  minor_lock; int /*<<< orphan*/  minor_idr; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct major_info* tap_get_major (int /*<<< orphan*/ ) ; 

void tap_free_minor(dev_t major, struct tap_dev *tap)
{
	struct major_info *tap_major;

	rcu_read_lock();
	tap_major = tap_get_major(MAJOR(major));
	if (!tap_major) {
		goto unlock;
	}

	spin_lock(&tap_major->minor_lock);
	if (tap->minor) {
		idr_remove(&tap_major->minor_idr, tap->minor);
		tap->minor = 0;
	}
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_read_unlock();
}