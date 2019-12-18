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
struct xfs_trans {int dummy; } ;
struct xfs_buf_log_item {int /*<<< orphan*/  __bli_format; int /*<<< orphan*/  bli_refcount; } ;
struct xfs_buf {struct xfs_trans* b_transp; struct xfs_buf_log_item* b_log_item; } ;
typedef  enum xfs_blft { ____Placeholder_xfs_blft } xfs_blft ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_blft_to_flags (int /*<<< orphan*/ *,int) ; 

void
xfs_trans_buf_set_type(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp,
	enum xfs_blft		type)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	if (!tp)
		return;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != NULL);
	ASSERT(atomic_read(&bip->bli_refcount) > 0);

	xfs_blft_to_flags(&bip->__bli_format, type);
}