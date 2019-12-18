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
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_extent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  efi_id; } ;
struct xfs_efi_log_item {TYPE_2__ efi_format; } ;
struct TYPE_3__ {unsigned int efd_nextents; int /*<<< orphan*/  efd_efi_id; } ;
struct xfs_efd_log_item {int /*<<< orphan*/  efd_item; TYPE_1__ efd_format; struct xfs_efi_log_item* efd_efip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int XFS_EFD_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  XFS_LI_EFD ; 
 struct xfs_efd_log_item* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 struct xfs_efd_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_efd_item_ops ; 
 int /*<<< orphan*/  xfs_efd_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xfs_efd_log_item *
xfs_trans_get_efd(
	struct xfs_trans		*tp,
	struct xfs_efi_log_item		*efip,
	unsigned int			nextents)
{
	struct xfs_efd_log_item		*efdp;

	ASSERT(nextents > 0);

	if (nextents > XFS_EFD_MAX_FAST_EXTENTS) {
		efdp = kmem_zalloc(sizeof(struct xfs_efd_log_item) +
				(nextents - 1) * sizeof(struct xfs_extent),
				0);
	} else {
		efdp = kmem_zone_zalloc(xfs_efd_zone, 0);
	}

	xfs_log_item_init(tp->t_mountp, &efdp->efd_item, XFS_LI_EFD,
			  &xfs_efd_item_ops);
	efdp->efd_efip = efip;
	efdp->efd_format.efd_nextents = nextents;
	efdp->efd_format.efd_efi_id = efip->efi_format.efi_id;

	xfs_trans_add_item(tp, &efdp->efd_item);
	return efdp;
}