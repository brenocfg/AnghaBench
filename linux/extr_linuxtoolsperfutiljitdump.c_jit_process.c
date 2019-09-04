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
typedef  int /*<<< orphan*/  u64 ;
struct perf_session {int /*<<< orphan*/  evlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_data {int dummy; } ;
struct machine {int dummy; } ;
struct jit_buf_desc {int /*<<< orphan*/  bytes_written; int /*<<< orphan*/  sample_type; struct machine* machine; struct perf_data* output; struct perf_session* session; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  jd ;

/* Variables and functions */
 scalar_t__ jit_detect (char*,int /*<<< orphan*/ ) ; 
 int jit_inject (struct jit_buf_desc*,char*) ; 
 int /*<<< orphan*/  memset (struct jit_buf_desc*,int /*<<< orphan*/ ,int) ; 
 struct perf_evsel* perf_evlist__first (int /*<<< orphan*/ ) ; 

int
jit_process(struct perf_session *session,
	    struct perf_data *output,
	    struct machine *machine,
	    char *filename,
	    pid_t pid,
	    u64 *nbytes)
{
	struct perf_evsel *first;
	struct jit_buf_desc jd;
	int ret;

	/*
	 * first, detect marker mmap (i.e., the jitdump mmap)
	 */
	if (jit_detect(filename, pid))
		return 0;

	memset(&jd, 0, sizeof(jd));

	jd.session = session;
	jd.output  = output;
	jd.machine = machine;

	/*
	 * track sample_type to compute id_all layout
	 * perf sets the same sample type to all events as of now
	 */
	first = perf_evlist__first(session->evlist);
	jd.sample_type = first->attr.sample_type;

	*nbytes = 0;

	ret = jit_inject(&jd, filename);
	if (!ret) {
		*nbytes = jd.bytes_written;
		ret = 1;
	}

	return ret;
}