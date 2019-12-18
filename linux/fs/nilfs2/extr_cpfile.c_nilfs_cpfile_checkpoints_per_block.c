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
struct TYPE_2__ {unsigned long mi_entries_per_block; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 

__attribute__((used)) static inline unsigned long
nilfs_cpfile_checkpoints_per_block(const struct inode *cpfile)
{
	return NILFS_MDT(cpfile)->mi_entries_per_block;
}