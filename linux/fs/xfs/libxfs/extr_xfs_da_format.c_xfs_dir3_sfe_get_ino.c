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
typedef  int /*<<< orphan*/  xfs_ino_t ;
struct xfs_dir2_sf_hdr {int dummy; } ;
struct xfs_dir2_sf_entry {int namelen; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_dir2_sf_get_ino (struct xfs_dir2_sf_hdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xfs_ino_t
xfs_dir3_sfe_get_ino(
	struct xfs_dir2_sf_hdr	*hdr,
	struct xfs_dir2_sf_entry *sfep)
{
	return xfs_dir2_sf_get_ino(hdr, &sfep->name[sfep->namelen + 1]);
}