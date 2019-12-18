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
struct f2fs_inode {int i_inline; } ;

/* Variables and functions */
 int F2FS_DATA_EXIST ; 
 int F2FS_PIN_FILE ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  FI_PIN_FILE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void recover_inline_flags(struct inode *inode, struct f2fs_inode *ri)
{
	if (ri->i_inline & F2FS_PIN_FILE)
		set_inode_flag(inode, FI_PIN_FILE);
	else
		clear_inode_flag(inode, FI_PIN_FILE);
	if (ri->i_inline & F2FS_DATA_EXIST)
		set_inode_flag(inode, FI_DATA_EXIST);
	else
		clear_inode_flag(inode, FI_DATA_EXIST);
}