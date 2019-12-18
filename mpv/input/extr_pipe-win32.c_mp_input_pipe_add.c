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
struct input_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_add_thread_src (struct input_ctx*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pipe_thread ; 

void mp_input_pipe_add(struct input_ctx *ictx, const char *filename)
{
    mp_input_add_thread_src(ictx, (void *)filename, read_pipe_thread);
}