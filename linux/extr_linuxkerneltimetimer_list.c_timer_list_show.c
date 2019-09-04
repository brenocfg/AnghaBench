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
struct timer_list_iter {int cpu; int /*<<< orphan*/  now; int /*<<< orphan*/  second_pass; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_cpu (struct seq_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_list_header (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_list_show(struct seq_file *m, void *v)
{
	struct timer_list_iter *iter = v;

	if (iter->cpu == -1 && !iter->second_pass)
		timer_list_header(m, iter->now);
	else if (!iter->second_pass)
		print_cpu(m, iter->cpu, iter->now);
#ifdef CONFIG_GENERIC_CLOCKEVENTS
	else if (iter->cpu == -1 && iter->second_pass)
		timer_list_show_tickdevices_header(m);
	else
		print_tickdevice(m, tick_get_device(iter->cpu), iter->cpu);
#endif
	return 0;
}