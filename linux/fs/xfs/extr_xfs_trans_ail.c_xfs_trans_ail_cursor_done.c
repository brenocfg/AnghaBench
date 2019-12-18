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
struct xfs_ail_cursor {int /*<<< orphan*/  list; int /*<<< orphan*/ * item; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void
xfs_trans_ail_cursor_done(
	struct xfs_ail_cursor	*cur)
{
	cur->item = NULL;
	list_del_init(&cur->list);
}