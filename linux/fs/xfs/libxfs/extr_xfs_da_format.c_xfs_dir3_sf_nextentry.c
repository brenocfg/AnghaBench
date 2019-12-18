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
struct xfs_dir2_sf_hdr {int dummy; } ;
struct xfs_dir2_sf_entry {int /*<<< orphan*/  namelen; } ;

/* Variables and functions */
 int xfs_dir3_sf_entsize (struct xfs_dir2_sf_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfs_dir2_sf_entry *
xfs_dir3_sf_nextentry(
	struct xfs_dir2_sf_hdr	*hdr,
	struct xfs_dir2_sf_entry *sfep)
{
	return (struct xfs_dir2_sf_entry *)
		((char *)sfep + xfs_dir3_sf_entsize(hdr, sfep->namelen));
}