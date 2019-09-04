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
struct inode {scalar_t__ i_blocks; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_inode_is_fast_symlink(struct inode *inode)
{
	return (S_ISLNK(inode->i_mode) &&
		inode->i_blocks == 0);
}