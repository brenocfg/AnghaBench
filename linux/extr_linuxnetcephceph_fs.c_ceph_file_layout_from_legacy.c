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
struct ceph_file_layout_legacy {int /*<<< orphan*/  fl_pg_pool; int /*<<< orphan*/  fl_object_size; int /*<<< orphan*/  fl_stripe_count; int /*<<< orphan*/  fl_stripe_unit; } ;
struct ceph_file_layout {scalar_t__ stripe_unit; scalar_t__ stripe_count; scalar_t__ object_size; int pool_id; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

void ceph_file_layout_from_legacy(struct ceph_file_layout *fl,
				  struct ceph_file_layout_legacy *legacy)
{
	fl->stripe_unit = le32_to_cpu(legacy->fl_stripe_unit);
	fl->stripe_count = le32_to_cpu(legacy->fl_stripe_count);
	fl->object_size = le32_to_cpu(legacy->fl_object_size);
	fl->pool_id = le32_to_cpu(legacy->fl_pg_pool);
	if (fl->pool_id == 0 && fl->stripe_unit == 0 &&
	    fl->stripe_count == 0 && fl->object_size == 0)
		fl->pool_id = -1;
}