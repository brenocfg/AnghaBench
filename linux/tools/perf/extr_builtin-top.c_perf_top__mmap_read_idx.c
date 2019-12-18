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
typedef  union perf_event {int dummy; } perf_event ;
struct record_opts {scalar_t__ overwrite; } ;
struct TYPE_2__ {int rotate; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  in; } ;
struct perf_top {TYPE_1__ qe; struct evlist* evlist; struct record_opts record_opts; } ;
struct mmap {int dummy; } ;
struct evlist {struct mmap* mmap; struct mmap* overwrite_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_timestamp ; 
 int ordered_events__queue (int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_evlist__parse_sample_timestamp (struct evlist*,union perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_mmap__consume (struct mmap*) ; 
 int /*<<< orphan*/  perf_mmap__read_done (struct mmap*) ; 
 union perf_event* perf_mmap__read_event (struct mmap*) ; 
 scalar_t__ perf_mmap__read_init (struct mmap*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_top__mmap_read_idx(struct perf_top *top, int idx)
{
	struct record_opts *opts = &top->record_opts;
	struct evlist *evlist = top->evlist;
	struct mmap *md;
	union perf_event *event;

	md = opts->overwrite ? &evlist->overwrite_mmap[idx] : &evlist->mmap[idx];
	if (perf_mmap__read_init(md) < 0)
		return;

	while ((event = perf_mmap__read_event(md)) != NULL) {
		int ret;

		ret = perf_evlist__parse_sample_timestamp(evlist, event, &last_timestamp);
		if (ret && ret != -1)
			break;

		ret = ordered_events__queue(top->qe.in, event, last_timestamp, 0);
		if (ret)
			break;

		perf_mmap__consume(md);

		if (top->qe.rotate) {
			pthread_mutex_lock(&top->qe.mutex);
			top->qe.rotate = false;
			pthread_cond_signal(&top->qe.cond);
			pthread_mutex_unlock(&top->qe.mutex);
		}
	}

	perf_mmap__read_done(md);
}