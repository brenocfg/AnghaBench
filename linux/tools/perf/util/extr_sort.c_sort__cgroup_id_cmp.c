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
struct TYPE_2__ {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;
struct hist_entry {TYPE_1__ cgroup_id; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ _sort__cgroup_dev_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _sort__cgroup_inode_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
sort__cgroup_id_cmp(struct hist_entry *left, struct hist_entry *right)
{
	int64_t ret;

	ret = _sort__cgroup_dev_cmp(right->cgroup_id.dev, left->cgroup_id.dev);
	if (ret != 0)
		return ret;

	return _sort__cgroup_inode_cmp(right->cgroup_id.ino,
				       left->cgroup_id.ino);
}