#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int system_wide; scalar_t__ uid; scalar_t__ pid; scalar_t__ tid; } ;
struct TYPE_21__ {int tail_synthesize; int no_inherit; int ignore_missing_thread; scalar_t__ full_auxtrace; TYPE_2__ target; int /*<<< orphan*/  no_inherit_set; int /*<<< orphan*/  no_samples; scalar_t__ overwrite; scalar_t__ record_switch_events; } ;
struct TYPE_18__ {scalar_t__ enabled; scalar_t__ time; } ;
struct record {int no_buildid_cache; int no_buildid; int buildid_all; int /*<<< orphan*/  itr; TYPE_8__* evlist; TYPE_7__ opts; scalar_t__ no_buildid_cache_set; scalar_t__ no_buildid_set; TYPE_1__ switch_output; } ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_22__ {scalar_t__ nr_entries; } ;
struct TYPE_20__ {int allow_aliases; scalar_t__ kptr_restrict; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ UINT_MAX ; 
 int __cmd_record (struct record*,int,char const**) ; 
 scalar_t__ __perf_evlist__add_default (TYPE_8__*,int) ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 int /*<<< orphan*/  alarm_sig_handler ; 
 int /*<<< orphan*/  auxtrace_record__free (int /*<<< orphan*/ ) ; 
 int auxtrace_record__options (int /*<<< orphan*/ ,TYPE_8__*,TYPE_7__*) ; 
 int bpf__setup_stdout (TYPE_8__*) ; 
 int /*<<< orphan*/  bpf__strerror_setup_stdout (TYPE_8__*,int,char*,int) ; 
 int /*<<< orphan*/  disable_buildid_cache () ; 
 scalar_t__ dry_run ; 
 int errno ; 
 scalar_t__ nr_cgroups ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_options_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_can_record_switch_events () ; 
 int perf_config (int /*<<< orphan*/ ,struct record*) ; 
 scalar_t__ perf_evlist__create_maps (TYPE_8__*,TYPE_2__*) ; 
 int /*<<< orphan*/  perf_evlist__delete (TYPE_8__*) ; 
 int /*<<< orphan*/  perf_evlist__exclude_kernel (TYPE_8__*) ; 
 TYPE_8__* perf_evlist__new () ; 
 int /*<<< orphan*/  perf_quiet_option () ; 
 int /*<<< orphan*/  perf_record_config ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ quiet ; 
 struct record record ; 
 int record__auxtrace_init (struct record*) ; 
 int /*<<< orphan*/  record_options ; 
 scalar_t__ record_opts__config (TYPE_7__*) ; 
 int /*<<< orphan*/  record_usage ; 
 int /*<<< orphan*/  set_option_nobuild (int /*<<< orphan*/ ,char,char*,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ switch_output_setup (struct record*) ; 
 int /*<<< orphan*/  symbol__exit () ; 
 int /*<<< orphan*/  symbol__init (int /*<<< orphan*/ *) ; 
 TYPE_6__ symbol_conf ; 
 scalar_t__ target__none (TYPE_2__*) ; 
 int target__parse_uid (TYPE_2__*) ; 
 int /*<<< orphan*/  target__strerror (TYPE_2__*,int,char*,int) ; 
 int target__validate (TYPE_2__*) ; 
 int /*<<< orphan*/  ui__error (char*,...) ; 
 int /*<<< orphan*/  ui__warning (char*,char*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int cmd_record(int argc, const char **argv)
{
	int err;
	struct record *rec = &record;
	char errbuf[BUFSIZ];

	setlocale(LC_ALL, "");

#ifndef HAVE_LIBBPF_SUPPORT
# define set_nobuild(s, l, c) set_option_nobuild(record_options, s, l, "NO_LIBBPF=1", c)
	set_nobuild('\0', "clang-path", true);
	set_nobuild('\0', "clang-opt", true);
# undef set_nobuild
#endif

#ifndef HAVE_BPF_PROLOGUE
# if !defined (HAVE_DWARF_SUPPORT)
#  define REASON  "NO_DWARF=1"
# elif !defined (HAVE_LIBBPF_SUPPORT)
#  define REASON  "NO_LIBBPF=1"
# else
#  define REASON  "this architecture doesn't support BPF prologue"
# endif
# define set_nobuild(s, l, c) set_option_nobuild(record_options, s, l, REASON, c)
	set_nobuild('\0', "vmlinux", true);
# undef set_nobuild
# undef REASON
#endif

	rec->evlist = perf_evlist__new();
	if (rec->evlist == NULL)
		return -ENOMEM;

	err = perf_config(perf_record_config, rec);
	if (err)
		return err;

	argc = parse_options(argc, argv, record_options, record_usage,
			    PARSE_OPT_STOP_AT_NON_OPTION);
	if (quiet)
		perf_quiet_option();

	/* Make system wide (-a) the default target. */
	if (!argc && target__none(&rec->opts.target))
		rec->opts.target.system_wide = true;

	if (nr_cgroups && !rec->opts.target.system_wide) {
		usage_with_options_msg(record_usage, record_options,
			"cgroup monitoring only available in system-wide mode");

	}
	if (rec->opts.record_switch_events &&
	    !perf_can_record_switch_events()) {
		ui__error("kernel does not support recording context switch events\n");
		parse_options_usage(record_usage, record_options, "switch-events", 0);
		return -EINVAL;
	}

	if (switch_output_setup(rec)) {
		parse_options_usage(record_usage, record_options, "switch-output", 0);
		return -EINVAL;
	}

	if (rec->switch_output.time) {
		signal(SIGALRM, alarm_sig_handler);
		alarm(rec->switch_output.time);
	}

	/*
	 * Allow aliases to facilitate the lookup of symbols for address
	 * filters. Refer to auxtrace_parse_filters().
	 */
	symbol_conf.allow_aliases = true;

	symbol__init(NULL);

	err = record__auxtrace_init(rec);
	if (err)
		goto out;

	if (dry_run)
		goto out;

	err = bpf__setup_stdout(rec->evlist);
	if (err) {
		bpf__strerror_setup_stdout(rec->evlist, err, errbuf, sizeof(errbuf));
		pr_err("ERROR: Setup BPF stdout failed: %s\n",
			 errbuf);
		goto out;
	}

	err = -ENOMEM;

	if (symbol_conf.kptr_restrict && !perf_evlist__exclude_kernel(rec->evlist))
		pr_warning(
"WARNING: Kernel address maps (/proc/{kallsyms,modules}) are restricted,\n"
"check /proc/sys/kernel/kptr_restrict.\n\n"
"Samples in kernel functions may not be resolved if a suitable vmlinux\n"
"file is not found in the buildid cache or in the vmlinux path.\n\n"
"Samples in kernel modules won't be resolved at all.\n\n"
"If some relocation was applied (e.g. kexec) symbols may be misresolved\n"
"even with a suitable vmlinux or kallsyms file.\n\n");

	if (rec->no_buildid_cache || rec->no_buildid) {
		disable_buildid_cache();
	} else if (rec->switch_output.enabled) {
		/*
		 * In 'perf record --switch-output', disable buildid
		 * generation by default to reduce data file switching
		 * overhead. Still generate buildid if they are required
		 * explicitly using
		 *
		 *  perf record --switch-output --no-no-buildid \
		 *              --no-no-buildid-cache
		 *
		 * Following code equals to:
		 *
		 * if ((rec->no_buildid || !rec->no_buildid_set) &&
		 *     (rec->no_buildid_cache || !rec->no_buildid_cache_set))
		 *         disable_buildid_cache();
		 */
		bool disable = true;

		if (rec->no_buildid_set && !rec->no_buildid)
			disable = false;
		if (rec->no_buildid_cache_set && !rec->no_buildid_cache)
			disable = false;
		if (disable) {
			rec->no_buildid = true;
			rec->no_buildid_cache = true;
			disable_buildid_cache();
		}
	}

	if (record.opts.overwrite)
		record.opts.tail_synthesize = true;

	if (rec->evlist->nr_entries == 0 &&
	    __perf_evlist__add_default(rec->evlist, !record.opts.no_samples) < 0) {
		pr_err("Not enough memory for event selector list\n");
		goto out;
	}

	if (rec->opts.target.tid && !rec->opts.no_inherit_set)
		rec->opts.no_inherit = true;

	err = target__validate(&rec->opts.target);
	if (err) {
		target__strerror(&rec->opts.target, err, errbuf, BUFSIZ);
		ui__warning("%s\n", errbuf);
	}

	err = target__parse_uid(&rec->opts.target);
	if (err) {
		int saved_errno = errno;

		target__strerror(&rec->opts.target, err, errbuf, BUFSIZ);
		ui__error("%s", errbuf);

		err = -saved_errno;
		goto out;
	}

	/* Enable ignoring missing threads when -u/-p option is defined. */
	rec->opts.ignore_missing_thread = rec->opts.target.uid != UINT_MAX || rec->opts.target.pid;

	err = -ENOMEM;
	if (perf_evlist__create_maps(rec->evlist, &rec->opts.target) < 0)
		usage_with_options(record_usage, record_options);

	err = auxtrace_record__options(rec->itr, rec->evlist, &rec->opts);
	if (err)
		goto out;

	/*
	 * We take all buildids when the file contains
	 * AUX area tracing data because we do not decode the
	 * trace because it would take too long.
	 */
	if (rec->opts.full_auxtrace)
		rec->buildid_all = true;

	if (record_opts__config(&rec->opts)) {
		err = -EINVAL;
		goto out;
	}

	err = __cmd_record(&record, argc, argv);
out:
	perf_evlist__delete(rec->evlist);
	symbol__exit();
	auxtrace_record__free(rec->itr);
	return err;
}