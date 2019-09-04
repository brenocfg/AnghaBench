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
struct trace_iterator {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cpu_file; int /*<<< orphan*/  seq; int /*<<< orphan*/  ent; TYPE_1__* trace; } ;
struct splice_pipe_desc {unsigned int nr_pages; int nr_pages_max; struct partial_page* partial; struct page** pages; int /*<<< orphan*/  spd_release; int /*<<< orphan*/ * ops; } ;
struct pipe_inode_info {int dummy; } ;
struct partial_page {int /*<<< orphan*/  len; scalar_t__ offset; } ;
struct page {int dummy; } ;
struct file {struct trace_iterator* private_data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int (* splice_read ) (struct trace_iterator*,struct file*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PIPE_DEF_BUFFERS ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 scalar_t__ splice_grow_spd (struct pipe_inode_info*,struct splice_pipe_desc*) ; 
 int /*<<< orphan*/  splice_shrink_spd (struct splice_pipe_desc*) ; 
 int splice_to_pipe (struct pipe_inode_info*,struct splice_pipe_desc*) ; 
 int stub1 (struct trace_iterator*,struct file*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ; 
 int /*<<< orphan*/  trace_access_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_access_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_event_read_lock () ; 
 int /*<<< orphan*/  trace_event_read_unlock () ; 
 int /*<<< orphan*/  trace_find_next_entry_inc (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_seq_init (int /*<<< orphan*/ *) ; 
 int trace_seq_to_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_used (int /*<<< orphan*/ *) ; 
 size_t tracing_fill_pipe_page (size_t,struct trace_iterator*) ; 
 int /*<<< orphan*/  tracing_pipe_buf_ops ; 
 int /*<<< orphan*/  tracing_spd_release_pipe ; 
 int tracing_wait_pipe (struct file*) ; 

__attribute__((used)) static ssize_t tracing_splice_read_pipe(struct file *filp,
					loff_t *ppos,
					struct pipe_inode_info *pipe,
					size_t len,
					unsigned int flags)
{
	struct page *pages_def[PIPE_DEF_BUFFERS];
	struct partial_page partial_def[PIPE_DEF_BUFFERS];
	struct trace_iterator *iter = filp->private_data;
	struct splice_pipe_desc spd = {
		.pages		= pages_def,
		.partial	= partial_def,
		.nr_pages	= 0, /* This gets updated below. */
		.nr_pages_max	= PIPE_DEF_BUFFERS,
		.ops		= &tracing_pipe_buf_ops,
		.spd_release	= tracing_spd_release_pipe,
	};
	ssize_t ret;
	size_t rem;
	unsigned int i;

	if (splice_grow_spd(pipe, &spd))
		return -ENOMEM;

	mutex_lock(&iter->mutex);

	if (iter->trace->splice_read) {
		ret = iter->trace->splice_read(iter, filp,
					       ppos, pipe, len, flags);
		if (ret)
			goto out_err;
	}

	ret = tracing_wait_pipe(filp);
	if (ret <= 0)
		goto out_err;

	if (!iter->ent && !trace_find_next_entry_inc(iter)) {
		ret = -EFAULT;
		goto out_err;
	}

	trace_event_read_lock();
	trace_access_lock(iter->cpu_file);

	/* Fill as many pages as possible. */
	for (i = 0, rem = len; i < spd.nr_pages_max && rem; i++) {
		spd.pages[i] = alloc_page(GFP_KERNEL);
		if (!spd.pages[i])
			break;

		rem = tracing_fill_pipe_page(rem, iter);

		/* Copy the data into the page, so we can start over. */
		ret = trace_seq_to_buffer(&iter->seq,
					  page_address(spd.pages[i]),
					  trace_seq_used(&iter->seq));
		if (ret < 0) {
			__free_page(spd.pages[i]);
			break;
		}
		spd.partial[i].offset = 0;
		spd.partial[i].len = trace_seq_used(&iter->seq);

		trace_seq_init(&iter->seq);
	}

	trace_access_unlock(iter->cpu_file);
	trace_event_read_unlock();
	mutex_unlock(&iter->mutex);

	spd.nr_pages = i;

	if (i)
		ret = splice_to_pipe(pipe, &spd);
	else
		ret = 0;
out:
	splice_shrink_spd(&spd);
	return ret;

out_err:
	mutex_unlock(&iter->mutex);
	goto out;
}