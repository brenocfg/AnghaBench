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
struct ceph_mon_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_SUB_MONMAP ; 
 int /*<<< orphan*/  CEPH_SUB_OSDMAP ; 
 int /*<<< orphan*/  __ceph_monc_want_map (struct ceph_mon_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __open_session (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  __schedule_delayed (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ceph_monc_open_session(struct ceph_mon_client *monc)
{
	mutex_lock(&monc->mutex);
	__ceph_monc_want_map(monc, CEPH_SUB_MONMAP, 0, true);
	__ceph_monc_want_map(monc, CEPH_SUB_OSDMAP, 0, false);
	__open_session(monc);
	__schedule_delayed(monc);
	mutex_unlock(&monc->mutex);
	return 0;
}