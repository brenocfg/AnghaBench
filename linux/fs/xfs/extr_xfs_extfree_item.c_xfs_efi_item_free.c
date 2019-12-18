#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ efi_nextents; } ;
struct TYPE_3__ {struct xfs_efi_log_item* li_lv_shadow; } ;
struct xfs_efi_log_item {TYPE_2__ efi_format; TYPE_1__ efi_item; } ;

/* Variables and functions */
 scalar_t__ XFS_EFI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  kmem_free (struct xfs_efi_log_item*) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_efi_log_item*) ; 
 int /*<<< orphan*/  xfs_efi_zone ; 

void
xfs_efi_item_free(
	struct xfs_efi_log_item	*efip)
{
	kmem_free(efip->efi_item.li_lv_shadow);
	if (efip->efi_format.efi_nextents > XFS_EFI_MAX_FAST_EXTENTS)
		kmem_free(efip);
	else
		kmem_zone_free(xfs_efi_zone, efip);
}