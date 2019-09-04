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
struct goldfish_pipe_dev {struct goldfish_pipe* first_signalled_pipe; } ;
struct goldfish_pipe {struct goldfish_pipe* next_signalled; TYPE_1__* prev_signalled; } ;
struct TYPE_2__ {struct goldfish_pipe* next_signalled; } ;

/* Variables and functions */

__attribute__((used)) static void signalled_pipes_remove_locked(struct goldfish_pipe_dev *dev,
	struct goldfish_pipe *pipe) {
	if (pipe->prev_signalled)
		pipe->prev_signalled->next_signalled = pipe->next_signalled;
	if (pipe->next_signalled)
		pipe->next_signalled->prev_signalled = pipe->prev_signalled;
	if (pipe == dev->first_signalled_pipe)
		dev->first_signalled_pipe = pipe->next_signalled;
	pipe->prev_signalled = NULL;
	pipe->next_signalled = NULL;
}