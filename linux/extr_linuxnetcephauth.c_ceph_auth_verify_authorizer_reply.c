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
struct ceph_authorizer {int dummy; } ;
struct ceph_auth_client {int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* verify_authorizer_reply ) (struct ceph_auth_client*,struct ceph_authorizer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ceph_auth_client*,struct ceph_authorizer*) ; 

int ceph_auth_verify_authorizer_reply(struct ceph_auth_client *ac,
				      struct ceph_authorizer *a)
{
	int ret = 0;

	mutex_lock(&ac->mutex);
	if (ac->ops && ac->ops->verify_authorizer_reply)
		ret = ac->ops->verify_authorizer_reply(ac, a);
	mutex_unlock(&ac->mutex);
	return ret;
}