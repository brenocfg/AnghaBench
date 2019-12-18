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
typedef  void* u32 ;
struct pyrf_evsel {int /*<<< orphan*/  evsel; } ;
struct perf_event_attr {int sample_type; scalar_t__ sample_freq; int size; void* sample_id_all; void* mmap_data; void* precise_ip; void* watermark; void* task; void* enable_on_exec; void* inherit_stat; void* freq; void* comm; void* context_switch; void* mmap; void* exclude_idle; void* exclude_hv; void* exclude_kernel; void* exclude_user; void* exclusive; void* pinned; void* inherit; void* disabled; scalar_t__ sample_period; int /*<<< orphan*/  bp_len; int /*<<< orphan*/  bp_addr; int /*<<< orphan*/  bp_type; int /*<<< orphan*/  wakeup_events; int /*<<< orphan*/  read_format; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_TID ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int*,int /*<<< orphan*/ *,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  evsel__init (int /*<<< orphan*/ *,struct perf_event_attr*,int) ; 

__attribute__((used)) static int pyrf_evsel__init(struct pyrf_evsel *pevsel,
			    PyObject *args, PyObject *kwargs)
{
	struct perf_event_attr attr = {
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
		.sample_type = PERF_SAMPLE_PERIOD | PERF_SAMPLE_TID,
	};
	static char *kwlist[] = {
		"type",
		"config",
		"sample_freq",
		"sample_period",
		"sample_type",
		"read_format",
		"disabled",
		"inherit",
		"pinned",
		"exclusive",
		"exclude_user",
		"exclude_kernel",
		"exclude_hv",
		"exclude_idle",
		"mmap",
		"context_switch",
		"comm",
		"freq",
		"inherit_stat",
		"enable_on_exec",
		"task",
		"watermark",
		"precise_ip",
		"mmap_data",
		"sample_id_all",
		"wakeup_events",
		"bp_type",
		"bp_addr",
		"bp_len",
		 NULL
	};
	u64 sample_period = 0;
	u32 disabled = 0,
	    inherit = 0,
	    pinned = 0,
	    exclusive = 0,
	    exclude_user = 0,
	    exclude_kernel = 0,
	    exclude_hv = 0,
	    exclude_idle = 0,
	    mmap = 0,
	    context_switch = 0,
	    comm = 0,
	    freq = 1,
	    inherit_stat = 0,
	    enable_on_exec = 0,
	    task = 0,
	    watermark = 0,
	    precise_ip = 0,
	    mmap_data = 0,
	    sample_id_all = 1;
	int idx = 0;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs,
					 "|iKiKKiiiiiiiiiiiiiiiiiiiiiiKK", kwlist,
					 &attr.type, &attr.config, &attr.sample_freq,
					 &sample_period, &attr.sample_type,
					 &attr.read_format, &disabled, &inherit,
					 &pinned, &exclusive, &exclude_user,
					 &exclude_kernel, &exclude_hv, &exclude_idle,
					 &mmap, &context_switch, &comm, &freq, &inherit_stat,
					 &enable_on_exec, &task, &watermark,
					 &precise_ip, &mmap_data, &sample_id_all,
					 &attr.wakeup_events, &attr.bp_type,
					 &attr.bp_addr, &attr.bp_len, &idx))
		return -1;

	/* union... */
	if (sample_period != 0) {
		if (attr.sample_freq != 0)
			return -1; /* FIXME: throw right exception */
		attr.sample_period = sample_period;
	}

	/* Bitfields */
	attr.disabled	    = disabled;
	attr.inherit	    = inherit;
	attr.pinned	    = pinned;
	attr.exclusive	    = exclusive;
	attr.exclude_user   = exclude_user;
	attr.exclude_kernel = exclude_kernel;
	attr.exclude_hv	    = exclude_hv;
	attr.exclude_idle   = exclude_idle;
	attr.mmap	    = mmap;
	attr.context_switch = context_switch;
	attr.comm	    = comm;
	attr.freq	    = freq;
	attr.inherit_stat   = inherit_stat;
	attr.enable_on_exec = enable_on_exec;
	attr.task	    = task;
	attr.watermark	    = watermark;
	attr.precise_ip	    = precise_ip;
	attr.mmap_data	    = mmap_data;
	attr.sample_id_all  = sample_id_all;
	attr.size	    = sizeof(attr);

	evsel__init(&pevsel->evsel, &attr, idx);
	return 0;
}