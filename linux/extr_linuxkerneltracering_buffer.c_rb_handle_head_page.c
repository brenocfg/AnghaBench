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
struct ring_buffer_per_cpu {int /*<<< orphan*/  tail_page; int /*<<< orphan*/  entries_bytes; int /*<<< orphan*/  overrun; } ;
struct buffer_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_PAGE_SIZE ; 
#define  RB_PAGE_HEAD 131 
#define  RB_PAGE_MOVED 130 
#define  RB_PAGE_NORMAL 129 
#define  RB_PAGE_UPDATE 128 
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 struct buffer_page* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rb_head_page_set_head (struct ring_buffer_per_cpu*,struct buffer_page*,struct buffer_page*,int const) ; 
 int rb_head_page_set_normal (struct ring_buffer_per_cpu*,struct buffer_page*,struct buffer_page*,int const) ; 
 int rb_head_page_set_update (struct ring_buffer_per_cpu*,struct buffer_page*,struct buffer_page*,int) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,struct buffer_page**) ; 
 int rb_page_entries (struct buffer_page*) ; 

__attribute__((used)) static int
rb_handle_head_page(struct ring_buffer_per_cpu *cpu_buffer,
		    struct buffer_page *tail_page,
		    struct buffer_page *next_page)
{
	struct buffer_page *new_head;
	int entries;
	int type;
	int ret;

	entries = rb_page_entries(next_page);

	/*
	 * The hard part is here. We need to move the head
	 * forward, and protect against both readers on
	 * other CPUs and writers coming in via interrupts.
	 */
	type = rb_head_page_set_update(cpu_buffer, next_page, tail_page,
				       RB_PAGE_HEAD);

	/*
	 * type can be one of four:
	 *  NORMAL - an interrupt already moved it for us
	 *  HEAD   - we are the first to get here.
	 *  UPDATE - we are the interrupt interrupting
	 *           a current move.
	 *  MOVED  - a reader on another CPU moved the next
	 *           pointer to its reader page. Give up
	 *           and try again.
	 */

	switch (type) {
	case RB_PAGE_HEAD:
		/*
		 * We changed the head to UPDATE, thus
		 * it is our responsibility to update
		 * the counters.
		 */
		local_add(entries, &cpu_buffer->overrun);
		local_sub(BUF_PAGE_SIZE, &cpu_buffer->entries_bytes);

		/*
		 * The entries will be zeroed out when we move the
		 * tail page.
		 */

		/* still more to do */
		break;

	case RB_PAGE_UPDATE:
		/*
		 * This is an interrupt that interrupt the
		 * previous update. Still more to do.
		 */
		break;
	case RB_PAGE_NORMAL:
		/*
		 * An interrupt came in before the update
		 * and processed this for us.
		 * Nothing left to do.
		 */
		return 1;
	case RB_PAGE_MOVED:
		/*
		 * The reader is on another CPU and just did
		 * a swap with our next_page.
		 * Try again.
		 */
		return 1;
	default:
		RB_WARN_ON(cpu_buffer, 1); /* WTF??? */
		return -1;
	}

	/*
	 * Now that we are here, the old head pointer is
	 * set to UPDATE. This will keep the reader from
	 * swapping the head page with the reader page.
	 * The reader (on another CPU) will spin till
	 * we are finished.
	 *
	 * We just need to protect against interrupts
	 * doing the job. We will set the next pointer
	 * to HEAD. After that, we set the old pointer
	 * to NORMAL, but only if it was HEAD before.
	 * otherwise we are an interrupt, and only
	 * want the outer most commit to reset it.
	 */
	new_head = next_page;
	rb_inc_page(cpu_buffer, &new_head);

	ret = rb_head_page_set_head(cpu_buffer, new_head, next_page,
				    RB_PAGE_NORMAL);

	/*
	 * Valid returns are:
	 *  HEAD   - an interrupt came in and already set it.
	 *  NORMAL - One of two things:
	 *            1) We really set it.
	 *            2) A bunch of interrupts came in and moved
	 *               the page forward again.
	 */
	switch (ret) {
	case RB_PAGE_HEAD:
	case RB_PAGE_NORMAL:
		/* OK */
		break;
	default:
		RB_WARN_ON(cpu_buffer, 1);
		return -1;
	}

	/*
	 * It is possible that an interrupt came in,
	 * set the head up, then more interrupts came in
	 * and moved it again. When we get back here,
	 * the page would have been set to NORMAL but we
	 * just set it back to HEAD.
	 *
	 * How do you detect this? Well, if that happened
	 * the tail page would have moved.
	 */
	if (ret == RB_PAGE_NORMAL) {
		struct buffer_page *buffer_tail_page;

		buffer_tail_page = READ_ONCE(cpu_buffer->tail_page);
		/*
		 * If the tail had moved passed next, then we need
		 * to reset the pointer.
		 */
		if (buffer_tail_page != tail_page &&
		    buffer_tail_page != next_page)
			rb_head_page_set_normal(cpu_buffer, new_head,
						next_page,
						RB_PAGE_HEAD);
	}

	/*
	 * If this was the outer most commit (the one that
	 * changed the original pointer from HEAD to UPDATE),
	 * then it is up to us to reset it to NORMAL.
	 */
	if (type == RB_PAGE_HEAD) {
		ret = rb_head_page_set_normal(cpu_buffer, next_page,
					      tail_page,
					      RB_PAGE_UPDATE);
		if (RB_WARN_ON(cpu_buffer,
			       ret != RB_PAGE_UPDATE))
			return -1;
	}

	return 0;
}