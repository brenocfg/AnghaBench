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
struct ceph_string {size_t len; int /*<<< orphan*/  str; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool_ns; } ;
struct ceph_inode_info {TYPE_1__ i_layout; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_string (struct ceph_string*) ; 
 struct ceph_string* ceph_try_get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t ceph_vxattrcb_layout_pool_namespace(struct ceph_inode_info *ci,
						   char *val, size_t size)
{
	ssize_t ret = 0;
	struct ceph_string *ns = ceph_try_get_string(ci->i_layout.pool_ns);

	if (ns) {
		ret = ns->len;
		if (ret <= size)
			memcpy(val, ns->str, ret);
		ceph_put_string(ns);
	}
	return ret;
}