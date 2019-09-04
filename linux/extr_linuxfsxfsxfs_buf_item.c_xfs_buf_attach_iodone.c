#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void (* li_cb ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  li_bio_list; } ;
typedef  TYPE_1__ xfs_log_item_t ;
struct TYPE_10__ {int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_li_list; } ;
typedef  TYPE_2__ xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_buf_iodone_callbacks ; 
 int xfs_buf_islocked (TYPE_2__*) ; 

void
xfs_buf_attach_iodone(
	xfs_buf_t	*bp,
	void		(*cb)(xfs_buf_t *, xfs_log_item_t *),
	xfs_log_item_t	*lip)
{
	ASSERT(xfs_buf_islocked(bp));

	lip->li_cb = cb;
	list_add_tail(&lip->li_bio_list, &bp->b_li_list);

	ASSERT(bp->b_iodone == NULL ||
	       bp->b_iodone == xfs_buf_iodone_callbacks);
	bp->b_iodone = xfs_buf_iodone_callbacks;
}