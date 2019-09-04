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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct whc_qset {int in_sw_list; int in_hw_list; int /*<<< orphan*/  qset_dma; TYPE_1__ qh; int /*<<< orphan*/  list_node; } ;
struct whc {int /*<<< orphan*/  async_list; int /*<<< orphan*/  async_removed_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qset_get_next_prev (struct whc*,struct whc_qset*,struct whc_qset**,struct whc_qset**) ; 
 int /*<<< orphan*/  whc_qset_set_link_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asl_qset_remove(struct whc *whc, struct whc_qset *qset)
{
	struct whc_qset *prev, *next;

	qset_get_next_prev(whc, qset, &next, &prev);

	list_move(&qset->list_node, &whc->async_removed_list);
	qset->in_sw_list = false;

	/*
	 * No more qsets in the ASL?  The caller must stop the ASL as
	 * it's no longer valid.
	 */
	if (list_empty(&whc->async_list))
		return;

	/* Remove from ASL. */
	whc_qset_set_link_ptr(&prev->qh.link, next->qset_dma);
	qset->in_hw_list = false;
}