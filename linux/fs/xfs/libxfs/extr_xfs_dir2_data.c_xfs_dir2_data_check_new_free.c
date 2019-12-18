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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct xfs_dir2_data_unused {scalar_t__ length; } ;
struct xfs_dir2_data_hdr {int dummy; } ;
struct xfs_dir2_data_free {scalar_t__ length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __this_address ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_failaddr_t
xfs_dir2_data_check_new_free(
	struct xfs_dir2_data_hdr	*hdr,
	struct xfs_dir2_data_free	*dfp,
	struct xfs_dir2_data_unused	*newdup)
{
	if (dfp == NULL)
		return __this_address;
	if (dfp->length != newdup->length)
		return __this_address;
	if (be16_to_cpu(dfp->offset) != (char *)newdup - (char *)hdr)
		return __this_address;
	return NULL;
}