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
struct perf_event_sample {TYPE_1__ header; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct perf_event_header {int dummy; } ;
typedef  int (* perf_event_print_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  enum bpf_perf_event_ret { ____Placeholder_bpf_perf_event_ret } bpf_perf_event_ret ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 scalar_t__ PERF_RECORD_LOST ; 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 

__attribute__((used)) static enum bpf_perf_event_ret bpf_perf_event_print(void *event, void *priv)
{
	struct perf_event_sample *e = event;
	perf_event_print_fn fn = priv;
	int ret;

	if (e->header.type == PERF_RECORD_SAMPLE) {
		ret = fn(e->data, e->size);
		if (ret != LIBBPF_PERF_EVENT_CONT)
			return ret;
	} else if (e->header.type == PERF_RECORD_LOST) {
		struct {
			struct perf_event_header header;
			__u64 id;
			__u64 lost;
		} *lost = (void *) e;
		printf("lost %lld events\n", lost->lost);
	} else {
		printf("unknown event type=%d size=%d\n",
		       e->header.type, e->header.size);
	}

	return LIBBPF_PERF_EVENT_CONT;
}