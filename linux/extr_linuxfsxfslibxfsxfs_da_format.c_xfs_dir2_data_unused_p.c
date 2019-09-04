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
struct xfs_dir2_data_unused {int dummy; } ;
struct xfs_dir2_data_hdr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct xfs_dir2_data_unused *
xfs_dir2_data_unused_p(struct xfs_dir2_data_hdr *hdr)
{
	return (struct xfs_dir2_data_unused *)
		((char *)hdr + sizeof(struct xfs_dir2_data_hdr));
}