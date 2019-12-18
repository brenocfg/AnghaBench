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
struct dnode_of_data {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRS_PER_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_truncate_data_blocks_range (struct dnode_of_data*,int /*<<< orphan*/ ) ; 

void f2fs_truncate_data_blocks(struct dnode_of_data *dn)
{
	f2fs_truncate_data_blocks_range(dn, ADDRS_PER_BLOCK(dn->inode));
}