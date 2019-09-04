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
struct ceph_osds {scalar_t__ primary; } ;

/* Variables and functions */
 scalar_t__ __osds_equal (struct ceph_osds const*,struct ceph_osds const*) ; 

__attribute__((used)) static bool osds_equal(const struct ceph_osds *lhs,
		       const struct ceph_osds *rhs)
{
	if (__osds_equal(lhs, rhs) &&
	    lhs->primary == rhs->primary)
		return true;

	return false;
}