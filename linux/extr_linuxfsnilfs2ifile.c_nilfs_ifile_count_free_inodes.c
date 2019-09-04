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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  inodes_count; } ;

/* Variables and functions */
 TYPE_2__* NILFS_I (struct inode*) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int nilfs_palloc_count_max_entries (struct inode*,scalar_t__,scalar_t__*) ; 

int nilfs_ifile_count_free_inodes(struct inode *ifile,
				    u64 *nmaxinodes, u64 *nfreeinodes)
{
	u64 nused;
	int err;

	*nmaxinodes = 0;
	*nfreeinodes = 0;

	nused = atomic64_read(&NILFS_I(ifile)->i_root->inodes_count);
	err = nilfs_palloc_count_max_entries(ifile, nused, nmaxinodes);
	if (likely(!err))
		*nfreeinodes = *nmaxinodes - nused;
	return err;
}