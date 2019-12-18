#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strfilter {int dummy; } ;
struct TYPE_2__ {scalar_t__ cache; } ;

/* Variables and functions */
 int __show_perf_probe_events (int,int,struct strfilter*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit_probe_symbol_maps () ; 
 int init_probe_symbol_maps (int) ; 
 int probe_cache__show_all_caches (struct strfilter*) ; 
 TYPE_1__ probe_conf ; 
 int probe_file__open_both (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_pager () ; 

int show_perf_probe_events(struct strfilter *filter)
{
	int kp_fd, up_fd, ret;

	setup_pager();

	if (probe_conf.cache)
		return probe_cache__show_all_caches(filter);

	ret = init_probe_symbol_maps(false);
	if (ret < 0)
		return ret;

	ret = probe_file__open_both(&kp_fd, &up_fd, 0);
	if (ret < 0)
		return ret;

	if (kp_fd >= 0)
		ret = __show_perf_probe_events(kp_fd, true, filter);
	if (up_fd >= 0 && ret >= 0)
		ret = __show_perf_probe_events(up_fd, false, filter);
	if (kp_fd > 0)
		close(kp_fd);
	if (up_fd > 0)
		close(up_fd);
	exit_probe_symbol_maps();

	return ret;
}