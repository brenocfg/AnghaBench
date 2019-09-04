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
struct timechart {int proc_num; scalar_t__ numcpus; int /*<<< orphan*/  tasks_only; int /*<<< orphan*/  turbo_frequency; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  last_time; int /*<<< orphan*/  first_time; scalar_t__ io_events; scalar_t__ power_only; } ;

/* Variables and functions */
 int BYTES_THRESH ; 
 int TIME_THRESH ; 
 int determine_display_io_tasks (struct timechart*,int) ; 
 int determine_display_tasks (struct timechart*,int) ; 
 int determine_display_tasks_filtered (struct timechart*) ; 
 int /*<<< orphan*/  draw_c_p_states (struct timechart*) ; 
 int /*<<< orphan*/  draw_cpu_usage (struct timechart*) ; 
 int /*<<< orphan*/  draw_io_bars (struct timechart*) ; 
 int /*<<< orphan*/  draw_process_bars (struct timechart*) ; 
 int /*<<< orphan*/  draw_wakeups (struct timechart*) ; 
 int /*<<< orphan*/  open_svg (char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ process_filter ; 
 int /*<<< orphan*/  svg_close () ; 
 int /*<<< orphan*/  svg_cpu_box (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_io_legenda () ; 
 int /*<<< orphan*/  svg_legenda () ; 
 int /*<<< orphan*/  svg_time_grid (double) ; 

__attribute__((used)) static void write_svg_file(struct timechart *tchart, const char *filename)
{
	u64 i;
	int count;
	int thresh = tchart->io_events ? BYTES_THRESH : TIME_THRESH;

	if (tchart->power_only)
		tchart->proc_num = 0;

	/* We'd like to show at least proc_num tasks;
	 * be less picky if we have fewer */
	do {
		if (process_filter)
			count = determine_display_tasks_filtered(tchart);
		else if (tchart->io_events)
			count = determine_display_io_tasks(tchart, thresh);
		else
			count = determine_display_tasks(tchart, thresh);
		thresh /= 10;
	} while (!process_filter && thresh && count < tchart->proc_num);

	if (!tchart->proc_num)
		count = 0;

	if (tchart->io_events) {
		open_svg(filename, 0, count, tchart->first_time, tchart->last_time);

		svg_time_grid(0.5);
		svg_io_legenda();

		draw_io_bars(tchart);
	} else {
		open_svg(filename, tchart->numcpus, count, tchart->first_time, tchart->last_time);

		svg_time_grid(0);

		svg_legenda();

		for (i = 0; i < tchart->numcpus; i++)
			svg_cpu_box(i, tchart->max_freq, tchart->turbo_frequency);

		draw_cpu_usage(tchart);
		if (tchart->proc_num)
			draw_process_bars(tchart);
		if (!tchart->tasks_only)
			draw_c_p_states(tchart);
		if (tchart->proc_num)
			draw_wakeups(tchart);
	}

	svg_close();
}