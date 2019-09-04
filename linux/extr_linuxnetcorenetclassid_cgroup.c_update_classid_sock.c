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
struct socket {TYPE_1__* sk; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_cgrp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_sk_update_lock ; 
 int /*<<< orphan*/  sock_cgroup_set_classid (int /*<<< orphan*/ *,unsigned long) ; 
 struct socket* sock_from_file (struct file*,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_classid_sock(const void *v, struct file *file, unsigned n)
{
	int err;
	struct socket *sock = sock_from_file(file, &err);

	if (sock) {
		spin_lock(&cgroup_sk_update_lock);
		sock_cgroup_set_classid(&sock->sk->sk_cgrp_data,
					(unsigned long)v);
		spin_unlock(&cgroup_sk_update_lock);
	}
	return 0;
}