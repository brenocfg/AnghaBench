#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dirparent; } ;
struct TYPE_4__ {TYPE_1__ new; } ;
struct adfs_dir {TYPE_2__ dirtail; int /*<<< orphan*/  parent_id; } ;

/* Variables and functions */
 unsigned int ADFS_NEWDIR_SIZE ; 
 int EIO ; 
 int adfs_dir_read (struct super_block*,int /*<<< orphan*/ ,unsigned int,struct adfs_dir*) ; 
 int /*<<< orphan*/  adfs_error (struct super_block*,char*) ; 
 int /*<<< orphan*/  adfs_readval (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adfs_f_read(struct super_block *sb, u32 indaddr, unsigned int size,
		       struct adfs_dir *dir)
{
	int ret;

	if (size != ADFS_NEWDIR_SIZE)
		return -EIO;

	ret = adfs_dir_read(sb, indaddr, size, dir);
	if (ret)
		adfs_error(sb, "unable to read directory");
	else
		dir->parent_id = adfs_readval(dir->dirtail.new.dirparent, 3);

	return ret;
}