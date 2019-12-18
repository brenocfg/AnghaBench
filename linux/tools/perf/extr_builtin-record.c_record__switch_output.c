#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timestamp ;
struct TYPE_8__ {int /*<<< orphan*/  target; } ;
struct TYPE_7__ {int num_files; int cur_file; char** filenames; } ;
struct perf_data {char* path; } ;
struct record {TYPE_4__ opts; TYPE_3__ switch_output; TYPE_2__* session; scalar_t__ bytes_written; scalar_t__ samples; struct perf_data data; } ;
struct TYPE_5__ {scalar_t__ data_size; int /*<<< orphan*/  data_offset; } ;
struct TYPE_6__ {TYPE_1__ header; } ;

/* Variables and functions */
 int EINVAL ; 
 int fetch_current_timestamp (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int perf_data__switch (struct perf_data*,char*,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  record__aio_mmap_read_sync (struct record*) ; 
 int /*<<< orphan*/  record__finish_output (struct record*) ; 
 int /*<<< orphan*/  record__synthesize (struct record*,int) ; 
 int /*<<< orphan*/  record__synthesize_workload (struct record*,int) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ target__none (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static int
record__switch_output(struct record *rec, bool at_exit)
{
	struct perf_data *data = &rec->data;
	int fd, err;
	char *new_filename;

	/* Same Size:      "2015122520103046"*/
	char timestamp[] = "InvalidTimestamp";

	record__aio_mmap_read_sync(rec);

	record__synthesize(rec, true);
	if (target__none(&rec->opts.target))
		record__synthesize_workload(rec, true);

	rec->samples = 0;
	record__finish_output(rec);
	err = fetch_current_timestamp(timestamp, sizeof(timestamp));
	if (err) {
		pr_err("Failed to get current timestamp\n");
		return -EINVAL;
	}

	fd = perf_data__switch(data, timestamp,
				    rec->session->header.data_offset,
				    at_exit, &new_filename);
	if (fd >= 0 && !at_exit) {
		rec->bytes_written = 0;
		rec->session->header.data_size = 0;
	}

	if (!quiet)
		fprintf(stderr, "[ perf record: Dump %s.%s ]\n",
			data->path, timestamp);

	if (rec->switch_output.num_files) {
		int n = rec->switch_output.cur_file + 1;

		if (n >= rec->switch_output.num_files)
			n = 0;
		rec->switch_output.cur_file = n;
		if (rec->switch_output.filenames[n]) {
			remove(rec->switch_output.filenames[n]);
			zfree(&rec->switch_output.filenames[n]);
		}
		rec->switch_output.filenames[n] = new_filename;
	} else {
		free(new_filename);
	}

	/* Output tracking events */
	if (!at_exit) {
		record__synthesize(rec, false);

		/*
		 * In 'perf record --switch-output' without -a,
		 * record__synthesize() in record__switch_output() won't
		 * generate tracking events because there's no thread_map
		 * in evlist. Which causes newly created perf.data doesn't
		 * contain map and comm information.
		 * Create a fake thread_map and directly call
		 * perf_event__synthesize_thread_map() for those events.
		 */
		if (target__none(&rec->opts.target))
			record__synthesize_workload(rec, false);
	}
	return fd;
}