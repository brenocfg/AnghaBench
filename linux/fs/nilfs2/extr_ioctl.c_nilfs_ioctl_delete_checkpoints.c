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
struct the_nilfs {struct inode* ns_cpfile; } ;
struct nilfs_period {int /*<<< orphan*/  p_end; int /*<<< orphan*/  p_start; } ;
struct nilfs_argv {size_t v_nmembs; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int nilfs_cpfile_delete_checkpoints (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_ioctl_delete_checkpoints(struct the_nilfs *nilfs,
					  struct nilfs_argv *argv, void *buf)
{
	size_t nmembs = argv->v_nmembs;
	struct inode *cpfile = nilfs->ns_cpfile;
	struct nilfs_period *periods = buf;
	int ret, i;

	for (i = 0; i < nmembs; i++) {
		ret = nilfs_cpfile_delete_checkpoints(
			cpfile, periods[i].p_start, periods[i].p_end);
		if (ret < 0)
			return ret;
	}
	return nmembs;
}