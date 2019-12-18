#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ceph_auth_client {int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* should_authenticate ) (struct ceph_auth_client*) ;} ;

/* Variables and functions */
 int ceph_build_auth_request (struct ceph_auth_client*,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct ceph_auth_client*) ; 

int ceph_build_auth(struct ceph_auth_client *ac,
		    void *msg_buf, size_t msg_len)
{
	int ret = 0;

	mutex_lock(&ac->mutex);
	if (ac->ops->should_authenticate(ac))
		ret = ceph_build_auth_request(ac, msg_buf, msg_len);
	mutex_unlock(&ac->mutex);
	return ret;
}