#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_extent_t ;
typedef  int /*<<< orphan*/  xfs_efd_log_format_t ;
struct TYPE_2__ {int efd_nextents; } ;
struct xfs_efd_log_item {TYPE_1__ efd_format; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_efd_item_sizeof(
	struct xfs_efd_log_item *efdp)
{
	return sizeof(xfs_efd_log_format_t) +
	       (efdp->efd_format.efd_nextents - 1) * sizeof(xfs_extent_t);
}