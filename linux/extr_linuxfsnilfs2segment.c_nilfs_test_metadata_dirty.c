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
struct the_nilfs {int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_cpfile; } ;
struct nilfs_root {int /*<<< orphan*/  ifile; } ;

/* Variables and functions */
 scalar_t__ nilfs_doing_gc () ; 
 scalar_t__ nilfs_mdt_fetch_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_test_metadata_dirty(struct the_nilfs *nilfs,
				     struct nilfs_root *root)
{
	int ret = 0;

	if (nilfs_mdt_fetch_dirty(root->ifile))
		ret++;
	if (nilfs_mdt_fetch_dirty(nilfs->ns_cpfile))
		ret++;
	if (nilfs_mdt_fetch_dirty(nilfs->ns_sufile))
		ret++;
	if ((ret || nilfs_doing_gc()) && nilfs_mdt_fetch_dirty(nilfs->ns_dat))
		ret++;
	return ret;
}