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
struct waiting_dir_move {int /*<<< orphan*/  node; } ;
struct send_ctx {int /*<<< orphan*/  waiting_dir_moves; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct waiting_dir_move*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_waiting_dir_move(struct send_ctx *sctx,
				  struct waiting_dir_move *dm)
{
	if (!dm)
		return;
	rb_erase(&dm->node, &sctx->waiting_dir_moves);
	kfree(dm);
}