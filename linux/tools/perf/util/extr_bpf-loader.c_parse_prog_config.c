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
struct perf_probe_event {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__CONFIG ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 int parse_perf_probe_command (char const*,struct perf_probe_event*) ; 
 char* parse_prog_config_kvpair (char const*,struct perf_probe_event*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
parse_prog_config(const char *config_str, const char **p_main_str,
		  bool *is_tp, struct perf_probe_event *pev)
{
	int err;
	const char *main_str = parse_prog_config_kvpair(config_str, pev);

	if (IS_ERR(main_str))
		return PTR_ERR(main_str);

	*p_main_str = main_str;
	if (!strchr(main_str, '=')) {
		/* Is a tracepoint event? */
		const char *s = strchr(main_str, ':');

		if (!s) {
			pr_debug("bpf: '%s' is not a valid tracepoint\n",
				 config_str);
			return -BPF_LOADER_ERRNO__CONFIG;
		}

		*is_tp = true;
		return 0;
	}

	*is_tp = false;
	err = parse_perf_probe_command(main_str, pev);
	if (err < 0) {
		pr_debug("bpf: '%s' is not a valid config string\n",
			 config_str);
		/* parse failed, don't need clear pev. */
		return -BPF_LOADER_ERRNO__CONFIG;
	}
	return 0;
}