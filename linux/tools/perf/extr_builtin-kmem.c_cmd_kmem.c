#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  env; } ;
struct perf_session {TYPE_2__ header; int /*<<< orphan*/  evlist; } ;
struct perf_data {int /*<<< orphan*/  path; int /*<<< orphan*/  force; int /*<<< orphan*/  mode; } ;
struct option {int dummy; } ;
struct evsel {TYPE_1__* tp_format; } ;
struct TYPE_6__ {int use_callchain; } ;
struct TYPE_4__ {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct perf_session*) ; 
 scalar_t__ KMEM_SLAB ; 
 int /*<<< orphan*/  LC_ALL ; 
 struct option const OPT_BOOLEAN (float,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_CALLBACK (char,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 struct option const OPT_CALLBACK_NOOPT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_STRING (char,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 int PTR_ERR (struct perf_session*) ; 
 int __cmd_kmem (struct perf_session*) ; 
 int __cmd_record (int,char const**) ; 
 scalar_t__ cpu__setup_cpunode_map () ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  kmem_config ; 
 scalar_t__ kmem_default ; 
 int kmem_page ; 
 int /*<<< orphan*/  kmem_page_size ; 
 struct perf_session* kmem_session ; 
 int kmem_slab ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  live_page ; 
 int /*<<< orphan*/  page_alloc_sort ; 
 int /*<<< orphan*/  page_alloc_sort_input ; 
 int /*<<< orphan*/  page_caller_sort ; 
 int /*<<< orphan*/  page_caller_sort_input ; 
 int /*<<< orphan*/  parse_alloc_opt ; 
 int /*<<< orphan*/  parse_caller_opt ; 
 int /*<<< orphan*/  parse_line_opt ; 
 int parse_options_subcommand (int,char const**,struct option const*,char const* const*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_page_opt ; 
 int /*<<< orphan*/  parse_slab_opt ; 
 int /*<<< orphan*/  parse_sort_opt ; 
 int perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct evsel* perf_evlist__find_tracepoint_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perf_kmem ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_time__parse_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char const*,...) ; 
 int /*<<< orphan*/  ptime ; 
 int /*<<< orphan*/  raw_ip ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup_page_sorting (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  setup_slab_sorting (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  slab_alloc_sort ; 
 int /*<<< orphan*/  slab_caller_sort ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  symbol__init (int /*<<< orphan*/ *) ; 
 TYPE_3__ symbol_conf ; 
 int /*<<< orphan*/  tep_get_page_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_str ; 
 int /*<<< orphan*/  usage_with_options (char const**,struct option const*) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_kmem(int argc, const char **argv)
{
	const char * const default_slab_sort = "frag,hit,bytes";
	const char * const default_page_sort = "bytes,hit";
	struct perf_data data = {
		.mode = PERF_DATA_MODE_READ,
	};
	const struct option kmem_options[] = {
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_CALLBACK_NOOPT(0, "caller", NULL, NULL,
			   "show per-callsite statistics", parse_caller_opt),
	OPT_CALLBACK_NOOPT(0, "alloc", NULL, NULL,
			   "show per-allocation statistics", parse_alloc_opt),
	OPT_CALLBACK('s', "sort", NULL, "key[,key2...]",
		     "sort by keys: ptr, callsite, bytes, hit, pingpong, frag, "
		     "page, order, migtype, gfp", parse_sort_opt),
	OPT_CALLBACK('l', "line", NULL, "num", "show n lines", parse_line_opt),
	OPT_BOOLEAN(0, "raw-ip", &raw_ip, "show raw ip instead of symbol"),
	OPT_BOOLEAN('f', "force", &data.force, "don't complain, do it"),
	OPT_CALLBACK_NOOPT(0, "slab", NULL, NULL, "Analyze slab allocator",
			   parse_slab_opt),
	OPT_CALLBACK_NOOPT(0, "page", NULL, NULL, "Analyze page allocator",
			   parse_page_opt),
	OPT_BOOLEAN(0, "live", &live_page, "Show live page stat"),
	OPT_STRING(0, "time", &time_str, "str",
		   "Time span of interest (start,stop)"),
	OPT_END()
	};
	const char *const kmem_subcommands[] = { "record", "stat", NULL };
	const char *kmem_usage[] = {
		NULL,
		NULL
	};
	struct perf_session *session;
	static const char errmsg[] = "No %s allocation events found.  Have you run 'perf kmem record --%s'?\n";
	int ret = perf_config(kmem_config, NULL);

	if (ret)
		return ret;

	argc = parse_options_subcommand(argc, argv, kmem_options,
					kmem_subcommands, kmem_usage, 0);

	if (!argc)
		usage_with_options(kmem_usage, kmem_options);

	if (kmem_slab == 0 && kmem_page == 0) {
		if (kmem_default == KMEM_SLAB)
			kmem_slab = 1;
		else
			kmem_page = 1;
	}

	if (!strncmp(argv[0], "rec", 3)) {
		symbol__init(NULL);
		return __cmd_record(argc, argv);
	}

	data.path = input_name;

	kmem_session = session = perf_session__new(&data, false, &perf_kmem);
	if (IS_ERR(session))
		return PTR_ERR(session);

	ret = -1;

	if (kmem_slab) {
		if (!perf_evlist__find_tracepoint_by_name(session->evlist,
							  "kmem:kmalloc")) {
			pr_err(errmsg, "slab", "slab");
			goto out_delete;
		}
	}

	if (kmem_page) {
		struct evsel *evsel;

		evsel = perf_evlist__find_tracepoint_by_name(session->evlist,
							     "kmem:mm_page_alloc");
		if (evsel == NULL) {
			pr_err(errmsg, "page", "page");
			goto out_delete;
		}

		kmem_page_size = tep_get_page_size(evsel->tp_format->tep);
		symbol_conf.use_callchain = true;
	}

	symbol__init(&session->header.env);

	if (perf_time__parse_str(&ptime, time_str) != 0) {
		pr_err("Invalid time string\n");
		ret = -EINVAL;
		goto out_delete;
	}

	if (!strcmp(argv[0], "stat")) {
		setlocale(LC_ALL, "");

		if (cpu__setup_cpunode_map())
			goto out_delete;

		if (list_empty(&slab_caller_sort))
			setup_slab_sorting(&slab_caller_sort, default_slab_sort);
		if (list_empty(&slab_alloc_sort))
			setup_slab_sorting(&slab_alloc_sort, default_slab_sort);
		if (list_empty(&page_caller_sort))
			setup_page_sorting(&page_caller_sort, default_page_sort);
		if (list_empty(&page_alloc_sort))
			setup_page_sorting(&page_alloc_sort, default_page_sort);

		if (kmem_page) {
			setup_page_sorting(&page_alloc_sort_input,
					   "page,order,migtype,gfp");
			setup_page_sorting(&page_caller_sort_input,
					   "callsite,order,migtype,gfp");
		}
		ret = __cmd_kmem(session);
	} else
		usage_with_options(kmem_usage, kmem_options);

out_delete:
	perf_session__delete(session);

	return ret;
}