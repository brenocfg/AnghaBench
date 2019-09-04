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
struct ceph_auth_handshake {int dummy; } ;
struct ceph_auth_client {int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* create_authorizer ) (struct ceph_auth_client*,int,struct ceph_auth_handshake*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ceph_auth_client*,int,struct ceph_auth_handshake*) ; 

int ceph_auth_create_authorizer(struct ceph_auth_client *ac,
				int peer_type,
				struct ceph_auth_handshake *auth)
{
	int ret = 0;

	mutex_lock(&ac->mutex);
	if (ac->ops && ac->ops->create_authorizer)
		ret = ac->ops->create_authorizer(ac, peer_type, auth);
	mutex_unlock(&ac->mutex);
	return ret;
}