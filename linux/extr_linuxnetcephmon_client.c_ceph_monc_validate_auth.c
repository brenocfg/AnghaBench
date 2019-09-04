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
 int __validate_auth (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ceph_monc_validate_auth(struct ceph_mon_client *monc)
{
	int ret;

	mutex_lock(&monc->mutex);
	ret = __validate_auth(monc);
	mutex_unlock(&monc->mutex);
	return ret;
}