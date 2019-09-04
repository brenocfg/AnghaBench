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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_post_read_required (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 

bool f2fs_may_inline_data(struct inode *inode)
{
	if (f2fs_is_atomic_file(inode))
		return false;

	if (!S_ISREG(inode->i_mode) && !S_ISLNK(inode->i_mode))
		return false;

	if (i_size_read(inode) > MAX_INLINE_DATA(inode))
		return false;

	if (f2fs_post_read_required(inode))
		return false;

	return true;
}