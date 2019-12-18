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
struct ceph_snap_context {scalar_t__ num_snaps; scalar_t__* snaps; scalar_t__ seq; } ;

/* Variables and functions */

__attribute__((used)) static bool has_new_snaps(struct ceph_snap_context *o,
			  struct ceph_snap_context *n)
{
	if (n->num_snaps == 0)
		return false;
	/* snaps are in descending order */
	return n->snaps[0] > o->seq;
}