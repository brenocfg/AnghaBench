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
struct ceph_auth_client {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct ceph_auth_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dout (char*,struct ceph_auth_client*) ; 
 int /*<<< orphan*/  kfree (struct ceph_auth_client*) ; 
 int /*<<< orphan*/  stub1 (struct ceph_auth_client*) ; 

void ceph_auth_destroy(struct ceph_auth_client *ac)
{
	dout("auth_destroy %p\n", ac);
	if (ac->ops)
		ac->ops->destroy(ac);
	kfree(ac);
}