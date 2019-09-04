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
typedef  scalar_t__ uint ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_efi_log_item {int dummy; } ;
struct xfs_efd_log_item {int /*<<< orphan*/  efd_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct xfs_efd_log_item* xfs_efd_init (int /*<<< orphan*/ ,struct xfs_efi_log_item*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

struct xfs_efd_log_item *
xfs_trans_get_efd(struct xfs_trans		*tp,
		  struct xfs_efi_log_item	*efip,
		  uint				nextents)
{
	struct xfs_efd_log_item			*efdp;

	ASSERT(tp != NULL);
	ASSERT(nextents > 0);

	efdp = xfs_efd_init(tp->t_mountp, efip, nextents);
	ASSERT(efdp != NULL);

	/*
	 * Get a log_item_desc to point at the new item.
	 */
	xfs_trans_add_item(tp, &efdp->efd_item);
	return efdp;
}