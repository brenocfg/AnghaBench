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
struct perf_session {int /*<<< orphan*/  data; scalar_t__ one_mmap_addr; scalar_t__ one_mmap_offset; scalar_t__ one_mmap; } ;
struct auxtrace_queues {int dummy; } ;
struct auxtrace_buffer {scalar_t__ size; int data_needs_freeing; scalar_t__ data; scalar_t__ data_offset; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 scalar_t__ BUFFER_LIMIT_FOR_32_BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  auxtrace_buffer__free (struct auxtrace_buffer*) ; 
 scalar_t__ auxtrace_copy_data (scalar_t__,struct perf_session*) ; 
 int auxtrace_queues__queue_buffer (struct auxtrace_queues*,unsigned int,struct auxtrace_buffer*) ; 
 int auxtrace_queues__split_buffer (struct auxtrace_queues*,unsigned int,struct auxtrace_buffer*) ; 
 scalar_t__ filter_cpu (struct perf_session*,int /*<<< orphan*/ ) ; 
 struct auxtrace_buffer* memdup (struct auxtrace_buffer*,int) ; 
 scalar_t__ perf_data__is_pipe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int auxtrace_queues__add_buffer(struct auxtrace_queues *queues,
				       struct perf_session *session,
				       unsigned int idx,
				       struct auxtrace_buffer *buffer,
				       struct auxtrace_buffer **buffer_ptr)
{
	int err = -ENOMEM;

	if (filter_cpu(session, buffer->cpu))
		return 0;

	buffer = memdup(buffer, sizeof(*buffer));
	if (!buffer)
		return -ENOMEM;

	if (session->one_mmap) {
		buffer->data = buffer->data_offset - session->one_mmap_offset +
			       session->one_mmap_addr;
	} else if (perf_data__is_pipe(session->data)) {
		buffer->data = auxtrace_copy_data(buffer->size, session);
		if (!buffer->data)
			goto out_free;
		buffer->data_needs_freeing = true;
	} else if (BITS_PER_LONG == 32 &&
		   buffer->size > BUFFER_LIMIT_FOR_32_BIT) {
		err = auxtrace_queues__split_buffer(queues, idx, buffer);
		if (err)
			goto out_free;
	}

	err = auxtrace_queues__queue_buffer(queues, idx, buffer);
	if (err)
		goto out_free;

	/* FIXME: Doesn't work for split buffer */
	if (buffer_ptr)
		*buffer_ptr = buffer;

	return 0;

out_free:
	auxtrace_buffer__free(buffer);
	return err;
}