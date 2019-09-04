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
struct TYPE_2__ {int type; scalar_t__ size; } ;
union perf_event {int /*<<< orphan*/  time_conv; TYPE_1__ header; } ;
typedef  scalar_t__ u64 ;
struct perf_tool {int (* attr ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ;int (* event_update ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ;int (* tracing_data ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* build_id ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* finished_round ) (struct perf_tool*,union perf_event*,struct ordered_events*) ;int (* id_index ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* auxtrace_info ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* auxtrace ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* auxtrace_error ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* thread_map ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* cpu_map ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* stat_config ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* stat ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* stat_round ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* time_conv ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* feature ) (struct perf_tool*,union perf_event*,struct perf_session*) ;} ;
struct ordered_events {int dummy; } ;
struct perf_session {int /*<<< orphan*/  time_conv; int /*<<< orphan*/  evlist; int /*<<< orphan*/  data; struct perf_tool* tool; struct ordered_events ordered_events; } ;
struct perf_sample {int /*<<< orphan*/  time; } ;
typedef  int s64 ;

/* Variables and functions */
 int EINVAL ; 
#define  PERF_RECORD_AUXTRACE 144 
#define  PERF_RECORD_AUXTRACE_ERROR 143 
#define  PERF_RECORD_AUXTRACE_INFO 142 
#define  PERF_RECORD_CPU_MAP 141 
#define  PERF_RECORD_EVENT_UPDATE 140 
#define  PERF_RECORD_FINISHED_ROUND 139 
#define  PERF_RECORD_HEADER_ATTR 138 
#define  PERF_RECORD_HEADER_BUILD_ID 137 
#define  PERF_RECORD_HEADER_EVENT_TYPE 136 
#define  PERF_RECORD_HEADER_FEATURE 135 
#define  PERF_RECORD_HEADER_TRACING_DATA 134 
#define  PERF_RECORD_ID_INDEX 133 
#define  PERF_RECORD_STAT 132 
#define  PERF_RECORD_STAT_CONFIG 131 
#define  PERF_RECORD_STAT_ROUND 130 
#define  PERF_RECORD_THREAD_MAP 129 
#define  PERF_RECORD_TIME_CONV 128 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  dump_event (int /*<<< orphan*/ ,union perf_event*,scalar_t__,struct perf_sample*) ; 
 int /*<<< orphan*/  lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int perf_data__fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__auxtrace_error_inc (struct perf_session*,union perf_event*) ; 
 int /*<<< orphan*/  perf_session__set_comm_exec (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (struct perf_session*) ; 
 int stub1 (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ; 
 int stub10 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub11 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub12 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub13 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub14 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub15 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub16 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub2 (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ; 
 int stub3 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub4 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub5 (struct perf_tool*,union perf_event*,struct ordered_events*) ; 
 int stub6 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub7 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub8 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub9 (struct perf_tool*,union perf_event*,struct perf_session*) ; 

__attribute__((used)) static s64 perf_session__process_user_event(struct perf_session *session,
					    union perf_event *event,
					    u64 file_offset)
{
	struct ordered_events *oe = &session->ordered_events;
	struct perf_tool *tool = session->tool;
	struct perf_sample sample = { .time = 0, };
	int fd = perf_data__fd(session->data);
	int err;

	dump_event(session->evlist, event, file_offset, &sample);

	/* These events are processed right away */
	switch (event->header.type) {
	case PERF_RECORD_HEADER_ATTR:
		err = tool->attr(tool, event, &session->evlist);
		if (err == 0) {
			perf_session__set_id_hdr_size(session);
			perf_session__set_comm_exec(session);
		}
		return err;
	case PERF_RECORD_EVENT_UPDATE:
		return tool->event_update(tool, event, &session->evlist);
	case PERF_RECORD_HEADER_EVENT_TYPE:
		/*
		 * Depreceated, but we need to handle it for sake
		 * of old data files create in pipe mode.
		 */
		return 0;
	case PERF_RECORD_HEADER_TRACING_DATA:
		/* setup for reading amidst mmap */
		lseek(fd, file_offset, SEEK_SET);
		return tool->tracing_data(tool, event, session);
	case PERF_RECORD_HEADER_BUILD_ID:
		return tool->build_id(tool, event, session);
	case PERF_RECORD_FINISHED_ROUND:
		return tool->finished_round(tool, event, oe);
	case PERF_RECORD_ID_INDEX:
		return tool->id_index(tool, event, session);
	case PERF_RECORD_AUXTRACE_INFO:
		return tool->auxtrace_info(tool, event, session);
	case PERF_RECORD_AUXTRACE:
		/* setup for reading amidst mmap */
		lseek(fd, file_offset + event->header.size, SEEK_SET);
		return tool->auxtrace(tool, event, session);
	case PERF_RECORD_AUXTRACE_ERROR:
		perf_session__auxtrace_error_inc(session, event);
		return tool->auxtrace_error(tool, event, session);
	case PERF_RECORD_THREAD_MAP:
		return tool->thread_map(tool, event, session);
	case PERF_RECORD_CPU_MAP:
		return tool->cpu_map(tool, event, session);
	case PERF_RECORD_STAT_CONFIG:
		return tool->stat_config(tool, event, session);
	case PERF_RECORD_STAT:
		return tool->stat(tool, event, session);
	case PERF_RECORD_STAT_ROUND:
		return tool->stat_round(tool, event, session);
	case PERF_RECORD_TIME_CONV:
		session->time_conv = event->time_conv;
		return tool->time_conv(tool, event, session);
	case PERF_RECORD_HEADER_FEATURE:
		return tool->feature(tool, event, session);
	default:
		return -EINVAL;
	}
}