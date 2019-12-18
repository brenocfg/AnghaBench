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
struct xfs_log_item {void (* li_cb ) (struct xfs_buf*,struct xfs_log_item*) ;int /*<<< orphan*/  li_bio_list; } ;
struct xfs_buf {int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_li_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_buf_iodone_callbacks ; 
 int xfs_buf_islocked (struct xfs_buf*) ; 

void
xfs_buf_attach_iodone(
	struct xfs_buf		*bp,
	void			(*cb)(struct xfs_buf *, struct xfs_log_item *),
	struct xfs_log_item	*lip)
{
	ASSERT(xfs_buf_islocked(bp));

	lip->li_cb = cb;
	list_add_tail(&lip->li_bio_list, &bp->b_li_list);

	ASSERT(bp->b_iodone == NULL ||
	       bp->b_iodone == xfs_buf_iodone_callbacks);
	bp->b_iodone = xfs_buf_iodone_callbacks;
}