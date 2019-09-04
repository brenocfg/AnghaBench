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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  OVL_DEDUPE ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int ovl_copyfile (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_inode_upper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_dedupe_file_range(struct file *file_in, loff_t pos_in,
				 struct file *file_out, loff_t pos_out, u64 len)
{
	/*
	 * Don't copy up because of a dedupe request, this wouldn't make sense
	 * most of the time (data would be duplicated instead of deduplicated).
	 */
	if (!ovl_inode_upper(file_inode(file_in)) ||
	    !ovl_inode_upper(file_inode(file_out)))
		return -EPERM;

	return ovl_copyfile(file_in, pos_in, file_out, pos_out, len, 0,
			    OVL_DEDUPE);
}