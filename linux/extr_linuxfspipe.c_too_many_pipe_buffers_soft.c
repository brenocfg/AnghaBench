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

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_user_pages_soft ; 

__attribute__((used)) static bool too_many_pipe_buffers_soft(unsigned long user_bufs)
{
	unsigned long soft_limit = READ_ONCE(pipe_user_pages_soft);

	return soft_limit && user_bufs > soft_limit;
}