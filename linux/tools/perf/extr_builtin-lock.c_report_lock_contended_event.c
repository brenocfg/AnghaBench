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
typedef  int /*<<< orphan*/  u64 ;
struct thread_stat {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; int /*<<< orphan*/  tid; } ;
struct lock_stat {int discard; int nr_contended; int avg_wait_time; int wait_time_total; } ;
struct lock_seq_stat {int state; int /*<<< orphan*/  prev_event_time; int /*<<< orphan*/  list; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 size_t BROKEN_CONTENDED ; 
 int /*<<< orphan*/  BUG_ON (char*) ; 
 int ENOMEM ; 
#define  SEQ_STATE_ACQUIRED 133 
#define  SEQ_STATE_ACQUIRING 132 
#define  SEQ_STATE_CONTENDED 131 
#define  SEQ_STATE_READ_ACQUIRED 130 
#define  SEQ_STATE_RELEASED 129 
#define  SEQ_STATE_UNINITIALIZED 128 
 int /*<<< orphan*/ * bad_hist ; 
 int /*<<< orphan*/  free (struct lock_seq_stat*) ; 
 struct lock_seq_stat* get_seq (struct thread_stat*,void*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct lock_stat* lock_stat_findnew (void*,char const*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 char* perf_evsel__strval (struct evsel*,struct perf_sample*,char*) ; 
 struct thread_stat* thread_stat_findnew (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int report_lock_contended_event(struct evsel *evsel,
				       struct perf_sample *sample)
{
	void *addr;
	struct lock_stat *ls;
	struct thread_stat *ts;
	struct lock_seq_stat *seq;
	const char *name = perf_evsel__strval(evsel, sample, "name");
	u64 tmp = perf_evsel__intval(evsel, sample, "lockdep_addr");

	memcpy(&addr, &tmp, sizeof(void *));

	ls = lock_stat_findnew(addr, name);
	if (!ls)
		return -ENOMEM;
	if (ls->discard)
		return 0;

	ts = thread_stat_findnew(sample->tid);
	if (!ts)
		return -ENOMEM;

	seq = get_seq(ts, addr);
	if (!seq)
		return -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIALIZED:
		/* orphan event, do nothing */
		return 0;
	case SEQ_STATE_ACQUIRING:
		break;
	case SEQ_STATE_RELEASED:
	case SEQ_STATE_ACQUIRED:
	case SEQ_STATE_READ_ACQUIRED:
	case SEQ_STATE_CONTENDED:
		/* broken lock sequence, discard it */
		ls->discard = 1;
		bad_hist[BROKEN_CONTENDED]++;
		list_del_init(&seq->list);
		free(seq);
		goto end;
	default:
		BUG_ON("Unknown state of lock sequence found!\n");
		break;
	}

	seq->state = SEQ_STATE_CONTENDED;
	ls->nr_contended++;
	ls->avg_wait_time = ls->wait_time_total/ls->nr_contended;
	seq->prev_event_time = sample->time;
end:
	return 0;
}