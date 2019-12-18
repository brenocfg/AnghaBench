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
struct evlist {int bkw_mmap_state; int /*<<< orphan*/  overwrite_mmap; } ;
typedef  enum bkw_mmap_state { ____Placeholder_bkw_mmap_state } bkw_mmap_state ;

/* Variables and functions */
#define  BKW_MMAP_DATA_PENDING 131 
#define  BKW_MMAP_EMPTY 130 
#define  BKW_MMAP_NOTREADY 129 
#define  BKW_MMAP_RUNNING 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  perf_evlist__pause (struct evlist*) ; 
 int /*<<< orphan*/  perf_evlist__resume (struct evlist*) ; 

void perf_evlist__toggle_bkw_mmap(struct evlist *evlist,
				  enum bkw_mmap_state state)
{
	enum bkw_mmap_state old_state = evlist->bkw_mmap_state;
	enum action {
		NONE,
		PAUSE,
		RESUME,
	} action = NONE;

	if (!evlist->overwrite_mmap)
		return;

	switch (old_state) {
	case BKW_MMAP_NOTREADY: {
		if (state != BKW_MMAP_RUNNING)
			goto state_err;
		break;
	}
	case BKW_MMAP_RUNNING: {
		if (state != BKW_MMAP_DATA_PENDING)
			goto state_err;
		action = PAUSE;
		break;
	}
	case BKW_MMAP_DATA_PENDING: {
		if (state != BKW_MMAP_EMPTY)
			goto state_err;
		break;
	}
	case BKW_MMAP_EMPTY: {
		if (state != BKW_MMAP_RUNNING)
			goto state_err;
		action = RESUME;
		break;
	}
	default:
		WARN_ONCE(1, "Shouldn't get there\n");
	}

	evlist->bkw_mmap_state = state;

	switch (action) {
	case PAUSE:
		perf_evlist__pause(evlist);
		break;
	case RESUME:
		perf_evlist__resume(evlist);
		break;
	case NONE:
	default:
		break;
	}

state_err:
	return;
}