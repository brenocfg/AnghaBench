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
struct trace_buffer {int /*<<< orphan*/ * data; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_buffer(struct trace_buffer *buf)
{
	if (buf->buffer) {
		ring_buffer_free(buf->buffer);
		buf->buffer = NULL;
		free_percpu(buf->data);
		buf->data = NULL;
	}
}