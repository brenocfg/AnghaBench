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
struct ceph_auth_none_info {int starting; } ;
struct ceph_auth_client {int /*<<< orphan*/ * ops; struct ceph_auth_none_info* private; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_AUTH_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ceph_auth_none_ops ; 
 int /*<<< orphan*/  dout (char*,struct ceph_auth_client*) ; 
 struct ceph_auth_none_info* kzalloc (int,int /*<<< orphan*/ ) ; 

int ceph_auth_none_init(struct ceph_auth_client *ac)
{
	struct ceph_auth_none_info *xi;

	dout("ceph_auth_none_init %p\n", ac);
	xi = kzalloc(sizeof(*xi), GFP_NOFS);
	if (!xi)
		return -ENOMEM;

	xi->starting = true;

	ac->protocol = CEPH_AUTH_NONE;
	ac->private = xi;
	ac->ops = &ceph_auth_none_ops;
	return 0;
}