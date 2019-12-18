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

/* Variables and functions */
 int XFS_INO64_DIFF ; 

__attribute__((used)) static inline int xfs_dir2_sf_hdr_size(int i8count)
{
	return sizeof(struct xfs_dir2_sf_hdr) -
		(i8count == 0) * XFS_INO64_DIFF;
}