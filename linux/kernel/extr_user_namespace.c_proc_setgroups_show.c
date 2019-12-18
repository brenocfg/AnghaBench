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
struct user_namespace {int /*<<< orphan*/  flags; } ;
struct seq_file {struct user_namespace* private; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long USERNS_SETGROUPS_ALLOWED ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

int proc_setgroups_show(struct seq_file *seq, void *v)
{
	struct user_namespace *ns = seq->private;
	unsigned long userns_flags = READ_ONCE(ns->flags);

	seq_printf(seq, "%s\n",
		   (userns_flags & USERNS_SETGROUPS_ALLOWED) ?
		   "allow" : "deny");
	return 0;
}