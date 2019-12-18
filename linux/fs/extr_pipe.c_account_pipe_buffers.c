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
struct user_struct {int /*<<< orphan*/  pipe_bufs; } ;

/* Variables and functions */
 unsigned long atomic_long_add_return (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long account_pipe_buffers(struct user_struct *user,
                                 unsigned long old, unsigned long new)
{
	return atomic_long_add_return(new - old, &user->pipe_bufs);
}