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
struct xfs_dir2_sf_hdr {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_dir2_sf_put_ino (struct xfs_dir2_sf_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_sf_put_parent_ino(
	struct xfs_dir2_sf_hdr	*hdr,
	xfs_ino_t		ino)
{
	xfs_dir2_sf_put_ino(hdr, hdr->parent, ino);
}