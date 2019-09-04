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
typedef  int /*<<< orphan*/  u64 ;
struct the_nilfs {struct nilfs_super_block** ns_sbp; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_dev_size; } ;
struct nilfs_dev_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ssize_t nilfs_dev_device_size_show(struct nilfs_dev_attr *attr,
				    struct the_nilfs *nilfs,
				    char *buf)
{
	struct nilfs_super_block **sbp = nilfs->ns_sbp;
	u64 dev_size = le64_to_cpu(sbp[0]->s_dev_size);

	return snprintf(buf, PAGE_SIZE, "%llu\n", dev_size);
}