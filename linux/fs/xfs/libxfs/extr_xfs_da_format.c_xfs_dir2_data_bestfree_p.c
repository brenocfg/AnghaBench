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
struct xfs_dir2_data_hdr {struct xfs_dir2_data_free* bestfree; } ;
struct xfs_dir2_data_free {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct xfs_dir2_data_free *
xfs_dir2_data_bestfree_p(struct xfs_dir2_data_hdr *hdr)
{
	return hdr->bestfree;
}