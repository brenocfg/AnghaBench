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
struct saved_cmdlines_buffer {struct saved_cmdlines_buffer* map_cmdline_to_pid; struct saved_cmdlines_buffer* saved_cmdlines; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct saved_cmdlines_buffer*) ; 

__attribute__((used)) static void free_saved_cmdlines_buffer(struct saved_cmdlines_buffer *s)
{
	kfree(s->saved_cmdlines);
	kfree(s->map_cmdline_to_pid);
	kfree(s);
}