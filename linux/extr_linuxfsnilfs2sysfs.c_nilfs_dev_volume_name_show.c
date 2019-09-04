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
struct the_nilfs {struct nilfs_super_block** ns_sbp; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_volume_name; } ;
struct nilfs_dev_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ssize_t nilfs_dev_volume_name_show(struct nilfs_dev_attr *attr,
				    struct the_nilfs *nilfs,
				    char *buf)
{
	struct nilfs_super_block **sbp = nilfs->ns_sbp;

	return scnprintf(buf, sizeof(sbp[0]->s_volume_name), "%s\n",
			 sbp[0]->s_volume_name);
}