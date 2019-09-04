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
typedef  int u32 ;
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_ndirtyblks; } ;
struct nilfs_segctor_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_segctor_dirty_data_blocks_count_show(struct nilfs_segctor_attr *attr,
					    struct the_nilfs *nilfs,
					    char *buf)
{
	u32 ndirtyblks;

	down_read(&nilfs->ns_segctor_sem);
	ndirtyblks = atomic_read(&nilfs->ns_ndirtyblks);
	up_read(&nilfs->ns_segctor_sem);

	return snprintf(buf, PAGE_SIZE, "%u\n", ndirtyblks);
}