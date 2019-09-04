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
struct TYPE_2__ {int efi_nextents; } ;
struct xfs_efi_log_item {TYPE_1__ efi_format; } ;
struct xfs_efi_log_format {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_efi_item_sizeof(
	struct xfs_efi_log_item *efip)
{
	return sizeof(struct xfs_efi_log_format) +
	       (efip->efi_format.efi_nextents - 1) * sizeof(xfs_extent_t);
}