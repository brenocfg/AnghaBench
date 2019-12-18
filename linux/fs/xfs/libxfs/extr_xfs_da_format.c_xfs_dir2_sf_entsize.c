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
struct xfs_dir2_sf_hdr {scalar_t__ i8count; } ;
struct xfs_dir2_sf_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_INO32_SIZE ; 
 scalar_t__ XFS_INO64_SIZE ; 

__attribute__((used)) static int
xfs_dir2_sf_entsize(
	struct xfs_dir2_sf_hdr	*hdr,
	int			len)
{
	int count = sizeof(struct xfs_dir2_sf_entry);	/* namelen + offset */

	count += len;					/* name */
	count += hdr->i8count ? XFS_INO64_SIZE : XFS_INO32_SIZE; /* ino # */
	return count;
}