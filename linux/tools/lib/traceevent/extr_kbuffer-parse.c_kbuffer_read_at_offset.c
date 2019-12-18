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
struct kbuffer {int start; int curr; int /*<<< orphan*/  subbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kbuffer_load_subbuffer (struct kbuffer*,int /*<<< orphan*/ ) ; 
 void* kbuffer_next_event (struct kbuffer*,unsigned long long*) ; 
 void* kbuffer_read_event (struct kbuffer*,unsigned long long*) ; 

void *kbuffer_read_at_offset(struct kbuffer *kbuf, int offset,
			     unsigned long long *ts)
{
	void *data;

	if (offset < kbuf->start)
		offset = 0;
	else
		offset -= kbuf->start;

	/* Reset the buffer */
	kbuffer_load_subbuffer(kbuf, kbuf->subbuffer);
	data = kbuffer_read_event(kbuf, ts);

	while (kbuf->curr < offset) {
		data = kbuffer_next_event(kbuf, ts);
		if (!data)
			break;
	}

	return data;
}