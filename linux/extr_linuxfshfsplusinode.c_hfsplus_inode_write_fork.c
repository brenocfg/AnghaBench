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
struct inode {int /*<<< orphan*/  i_size; } ;
struct hfsplus_fork_raw {int /*<<< orphan*/  total_blocks; int /*<<< orphan*/  total_size; int /*<<< orphan*/  extents; } ;
typedef  int /*<<< orphan*/  hfsplus_extent_rec ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_blocks; int /*<<< orphan*/  first_extents; } ;

/* Variables and functions */
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void hfsplus_inode_write_fork(struct inode *inode,
		struct hfsplus_fork_raw *fork)
{
	memcpy(&fork->extents, &HFSPLUS_I(inode)->first_extents,
	       sizeof(hfsplus_extent_rec));
	fork->total_size = cpu_to_be64(inode->i_size);
	fork->total_blocks = cpu_to_be32(HFSPLUS_I(inode)->alloc_blocks);
}