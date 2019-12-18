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
typedef  int /*<<< orphan*/  u32 ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__OPEN ; 
 scalar_t__ SOCKFS_MAGIC ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_to_av (struct file*) ; 
 scalar_t__ selinux_policycap_openperm () ; 

__attribute__((used)) static inline u32 open_file_to_av(struct file *file)
{
	u32 av = file_to_av(file);
	struct inode *inode = file_inode(file);

	if (selinux_policycap_openperm() &&
	    inode->i_sb->s_magic != SOCKFS_MAGIC)
		av |= FILE__OPEN;

	return av;
}