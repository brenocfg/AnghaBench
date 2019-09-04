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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;
struct hrtimer_clock_base {int /*<<< orphan*/  offset; int /*<<< orphan*/  get_time; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  hrtimer_resolution ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_active_timers (struct seq_file*,struct hrtimer_clock_base*,scalar_t__) ; 
 int /*<<< orphan*/  print_name_offset (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_base(struct seq_file *m, struct hrtimer_clock_base *base, u64 now)
{
	SEQ_printf(m, "  .base:       %pK\n", base);
	SEQ_printf(m, "  .index:      %d\n", base->index);

	SEQ_printf(m, "  .resolution: %u nsecs\n", hrtimer_resolution);

	SEQ_printf(m,   "  .get_time:   ");
	print_name_offset(m, base->get_time);
	SEQ_printf(m,   "\n");
#ifdef CONFIG_HIGH_RES_TIMERS
	SEQ_printf(m, "  .offset:     %Lu nsecs\n",
		   (unsigned long long) ktime_to_ns(base->offset));
#endif
	SEQ_printf(m,   "active timers:\n");
	print_active_timers(m, base, now + ktime_to_ns(base->offset));
}