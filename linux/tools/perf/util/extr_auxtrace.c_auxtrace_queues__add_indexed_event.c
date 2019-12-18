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
struct TYPE_2__ {scalar_t__ type; int size; } ;
union perf_event {TYPE_1__ header; } ;
struct perf_session {int dummy; } ;
struct perf_record_auxtrace {int dummy; } ;
struct auxtrace_queues {int dummy; } ;
typedef  size_t off_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PERF_RECORD_AUXTRACE ; 
 int PERF_SAMPLE_MAX_SIZE ; 
 int auxtrace_queues__add_event (struct auxtrace_queues*,struct perf_session*,union perf_event*,size_t,int /*<<< orphan*/ *) ; 
 int perf_session__peek_event (struct perf_session*,size_t,char*,int,union perf_event**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int auxtrace_queues__add_indexed_event(struct auxtrace_queues *queues,
					      struct perf_session *session,
					      off_t file_offset, size_t sz)
{
	union perf_event *event;
	int err;
	char buf[PERF_SAMPLE_MAX_SIZE];

	err = perf_session__peek_event(session, file_offset, buf,
				       PERF_SAMPLE_MAX_SIZE, &event, NULL);
	if (err)
		return err;

	if (event->header.type == PERF_RECORD_AUXTRACE) {
		if (event->header.size < sizeof(struct perf_record_auxtrace) ||
		    event->header.size != sz) {
			err = -EINVAL;
			goto out;
		}
		file_offset += event->header.size;
		err = auxtrace_queues__add_event(queues, session, event,
						 file_offset, NULL);
	}
out:
	return err;
}