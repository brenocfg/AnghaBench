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
struct pipe_buffer {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  anon_pipe_buf_nomerge_ops ; 
 int /*<<< orphan*/  anon_pipe_buf_ops ; 

void pipe_buf_mark_unmergeable(struct pipe_buffer *buf)
{
	if (buf->ops == &anon_pipe_buf_ops)
		buf->ops = &anon_pipe_buf_nomerge_ops;
}