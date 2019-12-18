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
struct inode {TYPE_1__* i_sb; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FS_VERITY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VERITY (struct inode*) ; 
 scalar_t__ ext4_verity_in_progress (struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 

__attribute__((used)) static inline loff_t ext4_readpage_limit(struct inode *inode)
{
	if (IS_ENABLED(CONFIG_FS_VERITY) &&
	    (IS_VERITY(inode) || ext4_verity_in_progress(inode)))
		return inode->i_sb->s_maxbytes;

	return i_size_read(inode);
}