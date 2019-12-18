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
struct super_block {int dummy; } ;
struct TYPE_2__ {int s_mount_opt; } ;

/* Variables and functions */
 int REISERFS_DATA_LOG ; 
 int REISERFS_DATA_ORDERED ; 
 int REISERFS_DATA_WRITEBACK ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 

__attribute__((used)) static void switch_data_mode(struct super_block *s, unsigned long mode)
{
	REISERFS_SB(s)->s_mount_opt &= ~((1 << REISERFS_DATA_LOG) |
					 (1 << REISERFS_DATA_ORDERED) |
					 (1 << REISERFS_DATA_WRITEBACK));
	REISERFS_SB(s)->s_mount_opt |= (1 << mode);
}