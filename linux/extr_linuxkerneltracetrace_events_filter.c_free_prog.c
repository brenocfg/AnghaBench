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
struct prog_entry {struct prog_entry* pred; } ;
struct event_filter {int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct prog_entry*) ; 
 struct prog_entry* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_prog(struct event_filter *filter)
{
	struct prog_entry *prog;
	int i;

	prog = rcu_access_pointer(filter->prog);
	if (!prog)
		return;

	for (i = 0; prog[i].pred; i++)
		kfree(prog[i].pred);
	kfree(prog);
}