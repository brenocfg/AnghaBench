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
struct tracing_data {int temp; scalar_t__ size; int /*<<< orphan*/  temp_file; } ;
struct tracepoint_path {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct tracing_data*) ; 
 struct tracepoint_path* get_tracepoints_path (struct list_head*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tracing_data* malloc (int) ; 
 int /*<<< orphan*/  mkstemp (int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int output_fd ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  put_tracepoints_path (struct tracepoint_path*) ; 
 int record_event_files (struct tracepoint_path*) ; 
 int record_ftrace_files (struct tracepoint_path*) ; 
 int record_ftrace_printk () ; 
 int record_header_files () ; 
 int record_proc_kallsyms () ; 
 int record_saved_cmdline () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int tracing_data_header () ; 
 int /*<<< orphan*/  zfree (struct tracing_data**) ; 

struct tracing_data *tracing_data_get(struct list_head *pattrs,
				      int fd, bool temp)
{
	struct tracepoint_path *tps;
	struct tracing_data *tdata;
	int err;

	output_fd = fd;

	tps = get_tracepoints_path(pattrs);
	if (!tps)
		return NULL;

	tdata = malloc(sizeof(*tdata));
	if (!tdata)
		return NULL;

	tdata->temp = temp;
	tdata->size = 0;

	if (temp) {
		int temp_fd;

		snprintf(tdata->temp_file, sizeof(tdata->temp_file),
			 "/tmp/perf-XXXXXX");
		if (!mkstemp(tdata->temp_file)) {
			pr_debug("Can't make temp file");
			free(tdata);
			return NULL;
		}

		temp_fd = open(tdata->temp_file, O_RDWR);
		if (temp_fd < 0) {
			pr_debug("Can't read '%s'", tdata->temp_file);
			free(tdata);
			return NULL;
		}

		/*
		 * Set the temp file the default output, so all the
		 * tracing data are stored into it.
		 */
		output_fd = temp_fd;
	}

	err = tracing_data_header();
	if (err)
		goto out;
	err = record_header_files();
	if (err)
		goto out;
	err = record_ftrace_files(tps);
	if (err)
		goto out;
	err = record_event_files(tps);
	if (err)
		goto out;
	err = record_proc_kallsyms();
	if (err)
		goto out;
	err = record_ftrace_printk();
	if (err)
		goto out;
	err = record_saved_cmdline();

out:
	/*
	 * All tracing data are stored by now, we can restore
	 * the default output file in case we used temp file.
	 */
	if (temp) {
		tdata->size = lseek(output_fd, 0, SEEK_CUR);
		close(output_fd);
		output_fd = fd;
	}

	if (err)
		zfree(&tdata);

	put_tracepoints_path(tps);
	return tdata;
}