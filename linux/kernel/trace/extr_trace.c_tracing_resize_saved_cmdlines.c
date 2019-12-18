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
struct saved_cmdlines_buffer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ allocate_cmdlines_buffer (unsigned int,struct saved_cmdlines_buffer*) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_saved_cmdlines_buffer (struct saved_cmdlines_buffer*) ; 
 int /*<<< orphan*/  kfree (struct saved_cmdlines_buffer*) ; 
 struct saved_cmdlines_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct saved_cmdlines_buffer* savedcmd ; 
 int /*<<< orphan*/  trace_cmdline_lock ; 

__attribute__((used)) static int tracing_resize_saved_cmdlines(unsigned int val)
{
	struct saved_cmdlines_buffer *s, *savedcmd_temp;

	s = kmalloc(sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	if (allocate_cmdlines_buffer(val, s) < 0) {
		kfree(s);
		return -ENOMEM;
	}

	arch_spin_lock(&trace_cmdline_lock);
	savedcmd_temp = savedcmd;
	savedcmd = s;
	arch_spin_unlock(&trace_cmdline_lock);
	free_saved_cmdlines_buffer(savedcmd_temp);

	return 0;
}