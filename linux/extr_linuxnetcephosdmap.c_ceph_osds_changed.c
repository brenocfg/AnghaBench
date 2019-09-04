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
struct ceph_osds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __osds_equal (struct ceph_osds const*,struct ceph_osds const*) ; 
 scalar_t__ primary_changed (struct ceph_osds const*,struct ceph_osds const*) ; 

bool ceph_osds_changed(const struct ceph_osds *old_acting,
		       const struct ceph_osds *new_acting,
		       bool any_change)
{
	if (primary_changed(old_acting, new_acting))
		return true;

	if (any_change && !__osds_equal(old_acting, new_acting))
		return true;

	return false;
}