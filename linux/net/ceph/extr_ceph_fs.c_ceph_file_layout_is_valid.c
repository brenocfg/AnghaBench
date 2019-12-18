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
struct ceph_file_layout {int stripe_unit; int stripe_count; int object_size; } ;
typedef  int __u32 ;

/* Variables and functions */
 int CEPH_MIN_STRIPE_UNIT ; 

int ceph_file_layout_is_valid(const struct ceph_file_layout *layout)
{
	__u32 su = layout->stripe_unit;
	__u32 sc = layout->stripe_count;
	__u32 os = layout->object_size;

	/* stripe unit, object size must be non-zero, 64k increment */
	if (!su || (su & (CEPH_MIN_STRIPE_UNIT-1)))
		return 0;
	if (!os || (os & (CEPH_MIN_STRIPE_UNIT-1)))
		return 0;
	/* object size must be a multiple of stripe unit */
	if (os < su || os % su)
		return 0;
	/* stripe count must be non-zero */
	if (!sc)
		return 0;
	return 1;
}