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
typedef  scalar_t__ u64 ;
struct auxtrace_queues {int dummy; } ;
struct auxtrace_buffer {scalar_t__ size; int consecutive; int /*<<< orphan*/  data_offset; } ;

/* Variables and functions */
 scalar_t__ BUFFER_LIMIT_FOR_32_BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  auxtrace_buffer__free (struct auxtrace_buffer*) ; 
 int auxtrace_queues__queue_buffer (struct auxtrace_queues*,unsigned int,struct auxtrace_buffer*) ; 
 struct auxtrace_buffer* memdup (struct auxtrace_buffer*,int) ; 

__attribute__((used)) static int auxtrace_queues__split_buffer(struct auxtrace_queues *queues,
					 unsigned int idx,
					 struct auxtrace_buffer *buffer)
{
	u64 sz = buffer->size;
	bool consecutive = false;
	struct auxtrace_buffer *b;
	int err;

	while (sz > BUFFER_LIMIT_FOR_32_BIT) {
		b = memdup(buffer, sizeof(struct auxtrace_buffer));
		if (!b)
			return -ENOMEM;
		b->size = BUFFER_LIMIT_FOR_32_BIT;
		b->consecutive = consecutive;
		err = auxtrace_queues__queue_buffer(queues, idx, b);
		if (err) {
			auxtrace_buffer__free(b);
			return err;
		}
		buffer->data_offset += BUFFER_LIMIT_FOR_32_BIT;
		sz -= BUFFER_LIMIT_FOR_32_BIT;
		consecutive = true;
	}

	buffer->size = sz;
	buffer->consecutive = consecutive;

	return 0;
}