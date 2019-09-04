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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int i_data_log ; 
 scalar_t__ reiserfs_data_log (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int reiserfs_file_data_log(struct inode *inode)
{
	if (reiserfs_data_log(inode->i_sb) ||
	    (REISERFS_I(inode)->i_flags & i_data_log))
		return 1;
	return 0;
}