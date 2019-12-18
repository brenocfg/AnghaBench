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
struct xfs_dir3_free_hdr {int dummy; } ;
struct xfs_dir2_free {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static __be16 *
xfs_dir3_free_bests_p(struct xfs_dir2_free *free)
{
	return (__be16 *)((char *)free + sizeof(struct xfs_dir3_free_hdr));
}