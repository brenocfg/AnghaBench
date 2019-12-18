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
struct the_nilfs {int dummy; } ;
struct nilfs_dev_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  nilfs_count_free_blocks (struct the_nilfs*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 

__attribute__((used)) static
ssize_t nilfs_dev_free_blocks_show(struct nilfs_dev_attr *attr,
				   struct the_nilfs *nilfs,
				   char *buf)
{
	sector_t free_blocks = 0;

	nilfs_count_free_blocks(nilfs, &free_blocks);
	return snprintf(buf, PAGE_SIZE, "%llu\n",
			(unsigned long long)free_blocks);
}