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
typedef  long u64 ;
struct timechart {scalar_t__ min_time; scalar_t__ merge_dist; int /*<<< orphan*/  io_events; } ;
struct per_pidcomm {long max_bytes; long total_bytes; struct io_sample* io_samples; } ;
struct per_pid {long total_bytes; struct per_pidcomm* current; } ;
struct io_sample {long end_time; int type; scalar_t__ start_time; long err; long bytes; scalar_t__ fd; struct io_sample* next; scalar_t__ merges; } ;

/* Variables and functions */
 int IOTYPE_READ ; 
 int IOTYPE_RX ; 
 int IOTYPE_TX ; 
 int IOTYPE_WRITE ; 
 struct per_pid* find_create_pid (struct timechart*,int) ; 
 int /*<<< orphan*/  free (struct io_sample*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int pid_end_io_sample(struct timechart *tchart, int pid, int type,
			     u64 end, long ret)
{
	struct per_pid *p = find_create_pid(tchart, pid);
	struct per_pidcomm *c = p->current;
	struct io_sample *sample, *prev;

	if (!c) {
		pr_warning("Invalid pidcomm!\n");
		return -1;
	}

	sample = c->io_samples;

	if (!sample) /* skip partially captured events */
		return 0;

	if (sample->end_time) {
		pr_warning("Skip invalid end event: "
			   "previous event already ended!\n");
		return 0;
	}

	if (sample->type != type) {
		pr_warning("Skip invalid end event: invalid event type!\n");
		return 0;
	}

	sample->end_time = end;
	prev = sample->next;

	/* we want to be able to see small and fast transfers, so make them
	 * at least min_time long, but don't overlap them */
	if (sample->end_time - sample->start_time < tchart->min_time)
		sample->end_time = sample->start_time + tchart->min_time;
	if (prev && sample->start_time < prev->end_time) {
		if (prev->err) /* try to make errors more visible */
			sample->start_time = prev->end_time;
		else
			prev->end_time = sample->start_time;
	}

	if (ret < 0) {
		sample->err = ret;
	} else if (type == IOTYPE_READ || type == IOTYPE_WRITE ||
		   type == IOTYPE_TX || type == IOTYPE_RX) {

		if ((u64)ret > c->max_bytes)
			c->max_bytes = ret;

		c->total_bytes += ret;
		p->total_bytes += ret;
		sample->bytes = ret;
	}

	/* merge two requests to make svg smaller and render-friendly */
	if (prev &&
	    prev->type == sample->type &&
	    prev->err == sample->err &&
	    prev->fd == sample->fd &&
	    prev->end_time + tchart->merge_dist >= sample->start_time) {

		sample->bytes += prev->bytes;
		sample->merges += prev->merges + 1;

		sample->start_time = prev->start_time;
		sample->next = prev->next;
		free(prev);

		if (!sample->err && sample->bytes > c->max_bytes)
			c->max_bytes = sample->bytes;
	}

	tchart->io_events++;

	return 0;
}