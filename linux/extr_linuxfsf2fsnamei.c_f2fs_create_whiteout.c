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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int S_IFCHR ; 
 int WHITEOUT_MODE ; 
 int __f2fs_tmpfile (struct inode*,int /*<<< orphan*/ *,int,struct inode**) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_create_whiteout(struct inode *dir, struct inode **whiteout)
{
	if (unlikely(f2fs_cp_error(F2FS_I_SB(dir))))
		return -EIO;

	return __f2fs_tmpfile(dir, NULL, S_IFCHR | WHITEOUT_MODE, whiteout);
}