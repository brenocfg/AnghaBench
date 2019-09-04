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
struct inode {scalar_t__ i_nlink; TYPE_1__* i_sb; int /*<<< orphan*/  __i_nlink; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_remove_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 

void drop_nlink(struct inode *inode)
{
	WARN_ON(inode->i_nlink == 0);
	inode->__i_nlink--;
	if (!inode->i_nlink)
		atomic_long_inc(&inode->i_sb->s_remove_count);
}