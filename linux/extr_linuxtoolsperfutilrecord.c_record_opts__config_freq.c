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
struct record_opts {int user_freq; scalar_t__ user_interval; int default_interval; int freq; scalar_t__ strict_freq; } ;

/* Variables and functions */
 int UINT_MAX ; 
 scalar_t__ ULLONG_MAX ; 
 scalar_t__ get_max_rate (unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*,unsigned int,...) ; 

__attribute__((used)) static int record_opts__config_freq(struct record_opts *opts)
{
	bool user_freq = opts->user_freq != UINT_MAX;
	unsigned int max_rate;

	if (opts->user_interval != ULLONG_MAX)
		opts->default_interval = opts->user_interval;
	if (user_freq)
		opts->freq = opts->user_freq;

	/*
	 * User specified count overrides default frequency.
	 */
	if (opts->default_interval)
		opts->freq = 0;
	else if (opts->freq) {
		opts->default_interval = opts->freq;
	} else {
		pr_err("frequency and count are zero, aborting\n");
		return -1;
	}

	if (get_max_rate(&max_rate))
		return 0;

	/*
	 * User specified frequency is over current maximum.
	 */
	if (user_freq && (max_rate < opts->freq)) {
		if (opts->strict_freq) {
			pr_err("error: Maximum frequency rate (%'u Hz) exceeded.\n"
			       "       Please use -F freq option with a lower value or consider\n"
			       "       tweaking /proc/sys/kernel/perf_event_max_sample_rate.\n",
			       max_rate);
			return -1;
		} else {
			pr_warning("warning: Maximum frequency rate (%'u Hz) exceeded, throttling from %'u Hz to %'u Hz.\n"
				   "         The limit can be raised via /proc/sys/kernel/perf_event_max_sample_rate.\n"
				   "         The kernel will lower it when perf's interrupts take too long.\n"
				   "         Use --strict-freq to disable this throttling, refusing to record.\n",
				   max_rate, opts->freq, max_rate);

			opts->freq = max_rate;
		}
	}

	/*
	 * Default frequency is over current maximum.
	 */
	if (max_rate < opts->freq) {
		pr_warning("Lowering default frequency rate to %u.\n"
			   "Please consider tweaking "
			   "/proc/sys/kernel/perf_event_max_sample_rate.\n",
			   max_rate);
		opts->freq = max_rate;
	}

	return 0;
}