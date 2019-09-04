#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {scalar_t__ f_version; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_get_htree_eof (struct file*) ; 
 int /*<<< orphan*/  ext4_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generic_file_llseek_size (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ inode_peek_iversion (struct inode*) ; 
 int is_dx_dir (struct inode*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static loff_t ext4_dir_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	int dx_dir = is_dx_dir(inode);
	loff_t ret, htree_max = ext4_get_htree_eof(file);

	if (likely(dx_dir))
		ret = generic_file_llseek_size(file, offset, whence,
						    htree_max, htree_max);
	else
		ret = ext4_llseek(file, offset, whence);
	file->f_version = inode_peek_iversion(inode) - 1;
	return ret;
}