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
struct TYPE_2__ {scalar_t__ nr_cpus_avail; } ;
struct perf_header {TYPE_1__ env; } ;
struct perf_session {struct perf_header header; } ;
struct ctf_writer {int stream_cnt; struct ctf_stream** stream; } ;
struct ctf_stream {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct ctf_stream** zalloc (int) ; 

__attribute__((used)) static int setup_streams(struct ctf_writer *cw, struct perf_session *session)
{
	struct ctf_stream **stream;
	struct perf_header *ph = &session->header;
	int ncpus;

	/*
	 * Try to get the number of cpus used in the data file,
	 * if not present fallback to the MAX_CPUS.
	 */
	ncpus = ph->env.nr_cpus_avail ?: MAX_CPUS;

	stream = zalloc(sizeof(*stream) * ncpus);
	if (!stream) {
		pr_err("Failed to allocate streams.\n");
		return -ENOMEM;
	}

	cw->stream     = stream;
	cw->stream_cnt = ncpus;
	return 0;
}