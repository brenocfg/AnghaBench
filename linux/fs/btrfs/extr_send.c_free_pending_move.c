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
struct pending_dir_move {int /*<<< orphan*/  update_refs; int /*<<< orphan*/  node; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __free_recorded_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pending_dir_move*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pending_move(struct send_ctx *sctx, struct pending_dir_move *m)
{
	if (!list_empty(&m->list))
		list_del(&m->list);
	if (!RB_EMPTY_NODE(&m->node))
		rb_erase(&m->node, &sctx->pending_dir_moves);
	__free_recorded_refs(&m->update_refs);
	kfree(m);
}