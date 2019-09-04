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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ nilfs_cpfile_get_blkoff (struct inode const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nilfs_cpfile_is_in_first(const struct inode *cpfile,
					   __u64 cno)
{
	return nilfs_cpfile_get_blkoff(cpfile, cno) == 0;
}