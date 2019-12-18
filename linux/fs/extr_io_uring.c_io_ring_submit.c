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
struct sqe_submit {int has_user; int needs_lock; int needs_fixed_file; int /*<<< orphan*/  sequence; TYPE_1__* sqe; } ;
struct io_submit_state {int dummy; } ;
struct io_ring_ctx {int dummy; } ;
struct io_kiocb {int flags; int /*<<< orphan*/  submit; int /*<<< orphan*/  sequence; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IOSQE_IO_DRAIN ; 
 int IOSQE_IO_LINK ; 
 unsigned int IO_PLUG_THRESHOLD ; 
 int REQ_F_IO_DRAIN ; 
 int REQ_F_SHADOW_DRAIN ; 
 int /*<<< orphan*/  io_commit_sqring (struct io_ring_ctx*) ; 
 struct io_kiocb* io_get_req (struct io_ring_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_get_sqring (struct io_ring_ctx*,struct sqe_submit*) ; 
 int /*<<< orphan*/  io_queue_link_head (struct io_ring_ctx*,struct io_kiocb*,int /*<<< orphan*/ *,struct io_kiocb*) ; 
 int /*<<< orphan*/  io_submit_sqe (struct io_ring_ctx*,struct sqe_submit*,struct io_submit_state*,struct io_kiocb**) ; 
 int /*<<< orphan*/  io_submit_state_end (struct io_submit_state*) ; 
 int /*<<< orphan*/  io_submit_state_start (struct io_submit_state*,struct io_ring_ctx*,unsigned int) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_ring_submit(struct io_ring_ctx *ctx, unsigned int to_submit)
{
	struct io_submit_state state, *statep = NULL;
	struct io_kiocb *link = NULL;
	struct io_kiocb *shadow_req = NULL;
	bool prev_was_link = false;
	int i, submit = 0;

	if (to_submit > IO_PLUG_THRESHOLD) {
		io_submit_state_start(&state, ctx, to_submit);
		statep = &state;
	}

	for (i = 0; i < to_submit; i++) {
		struct sqe_submit s;

		if (!io_get_sqring(ctx, &s))
			break;

		/*
		 * If previous wasn't linked and we have a linked command,
		 * that's the end of the chain. Submit the previous link.
		 */
		if (!prev_was_link && link) {
			io_queue_link_head(ctx, link, &link->submit, shadow_req);
			link = NULL;
			shadow_req = NULL;
		}
		prev_was_link = (s.sqe->flags & IOSQE_IO_LINK) != 0;

		if (link && (s.sqe->flags & IOSQE_IO_DRAIN)) {
			if (!shadow_req) {
				shadow_req = io_get_req(ctx, NULL);
				if (unlikely(!shadow_req))
					goto out;
				shadow_req->flags |= (REQ_F_IO_DRAIN | REQ_F_SHADOW_DRAIN);
				refcount_dec(&shadow_req->refs);
			}
			shadow_req->sequence = s.sequence;
		}

out:
		s.has_user = true;
		s.needs_lock = false;
		s.needs_fixed_file = false;
		submit++;
		io_submit_sqe(ctx, &s, statep, &link);
	}

	if (link)
		io_queue_link_head(ctx, link, &link->submit, shadow_req);
	if (statep)
		io_submit_state_end(statep);

	io_commit_sqring(ctx);

	return submit;
}