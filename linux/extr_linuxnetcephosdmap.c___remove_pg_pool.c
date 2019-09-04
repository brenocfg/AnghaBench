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
struct rb_root {int dummy; } ;
struct ceph_pg_pool_info {struct ceph_pg_pool_info* name; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ceph_pg_pool_info*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 

__attribute__((used)) static void __remove_pg_pool(struct rb_root *root, struct ceph_pg_pool_info *pi)
{
	rb_erase(&pi->node, root);
	kfree(pi->name);
	kfree(pi);
}