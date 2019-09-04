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
struct nilfs_snapshot_attr {int dummy; } ;
struct nilfs_root {int /*<<< orphan*/  blocks_count; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t
nilfs_snapshot_blocks_count_show(struct nilfs_snapshot_attr *attr,
				 struct nilfs_root *root, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%llu\n",
			(unsigned long long)atomic64_read(&root->blocks_count));
}