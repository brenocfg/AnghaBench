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
struct send_ctx {int /*<<< orphan*/  pending_dir_moves; } ;
struct pending_dir_move {int /*<<< orphan*/  node; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tail_append_pending_moves(struct send_ctx *sctx,
				      struct pending_dir_move *moves,
				      struct list_head *stack)
{
	if (list_empty(&moves->list)) {
		list_add_tail(&moves->list, stack);
	} else {
		LIST_HEAD(list);
		list_splice_init(&moves->list, &list);
		list_add_tail(&moves->list, stack);
		list_splice_tail(&list, stack);
	}
	if (!RB_EMPTY_NODE(&moves->node)) {
		rb_erase(&moves->node, &sctx->pending_dir_moves);
		RB_CLEAR_NODE(&moves->node);
	}
}