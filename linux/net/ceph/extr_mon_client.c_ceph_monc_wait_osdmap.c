#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; TYPE_2__* subs; TYPE_1__* client; } ;
struct TYPE_4__ {scalar_t__ have; } ;
struct TYPE_3__ {int /*<<< orphan*/  auth_wq; } ;

/* Variables and functions */
 size_t CEPH_SUB_OSDMAP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ceph_monc_wait_osdmap(struct ceph_mon_client *monc, u32 epoch,
			  unsigned long timeout)
{
	unsigned long started = jiffies;
	long ret;

	mutex_lock(&monc->mutex);
	while (monc->subs[CEPH_SUB_OSDMAP].have < epoch) {
		mutex_unlock(&monc->mutex);

		if (timeout && time_after_eq(jiffies, started + timeout))
			return -ETIMEDOUT;

		ret = wait_event_interruptible_timeout(monc->client->auth_wq,
				     monc->subs[CEPH_SUB_OSDMAP].have >= epoch,
				     ceph_timeout_jiffies(timeout));
		if (ret < 0)
			return ret;

		mutex_lock(&monc->mutex);
	}

	mutex_unlock(&monc->mutex);
	return 0;
}