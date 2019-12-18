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
struct io_submit_state {size_t cur_req; int /*<<< orphan*/ * reqs; scalar_t__ free_reqs; int /*<<< orphan*/  plug; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_finish_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_file_put (struct io_submit_state*) ; 
 int /*<<< orphan*/  kmem_cache_free_bulk (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_cachep ; 

__attribute__((used)) static void io_submit_state_end(struct io_submit_state *state)
{
	blk_finish_plug(&state->plug);
	io_file_put(state);
	if (state->free_reqs)
		kmem_cache_free_bulk(req_cachep, state->free_reqs,
					&state->reqs[state->cur_req]);
}