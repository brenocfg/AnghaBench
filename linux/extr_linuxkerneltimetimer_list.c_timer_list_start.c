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
struct timer_list_iter {int cpu; int second_pass; int /*<<< orphan*/  now; } ;
struct seq_file {struct timer_list_iter* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 void* move_iter (struct timer_list_iter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *timer_list_start(struct seq_file *file, loff_t *offset)
{
	struct timer_list_iter *iter = file->private;

	if (!*offset)
		iter->now = ktime_to_ns(ktime_get());
	iter->cpu = -1;
	iter->second_pass = false;
	return move_iter(iter, *offset);
}