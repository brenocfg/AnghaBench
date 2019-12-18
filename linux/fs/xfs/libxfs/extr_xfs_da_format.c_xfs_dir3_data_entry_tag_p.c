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
struct xfs_dir2_data_entry {int /*<<< orphan*/  namelen; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int xfs_dir3_data_entsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 *
xfs_dir3_data_entry_tag_p(
	struct xfs_dir2_data_entry *dep)
{
	return (__be16 *)((char *)dep +
		xfs_dir3_data_entsize(dep->namelen) - sizeof(__be16));
}