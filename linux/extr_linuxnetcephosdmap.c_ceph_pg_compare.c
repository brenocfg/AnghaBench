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
struct ceph_pg {scalar_t__ pool; scalar_t__ seed; } ;

/* Variables and functions */

int ceph_pg_compare(const struct ceph_pg *lhs, const struct ceph_pg *rhs)
{
	if (lhs->pool < rhs->pool)
		return -1;
	if (lhs->pool > rhs->pool)
		return 1;
	if (lhs->seed < rhs->seed)
		return -1;
	if (lhs->seed > rhs->seed)
		return 1;

	return 0;
}