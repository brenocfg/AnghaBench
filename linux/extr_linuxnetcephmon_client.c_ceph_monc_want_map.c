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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __ceph_monc_want_map (struct ceph_mon_client*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool ceph_monc_want_map(struct ceph_mon_client *monc, int sub, u32 epoch,
			bool continuous)
{
	bool need_request;

	mutex_lock(&monc->mutex);
	need_request = __ceph_monc_want_map(monc, sub, epoch, continuous);
	mutex_unlock(&monc->mutex);

	return need_request;
}