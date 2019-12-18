#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {scalar_t__ type; } ;
union perf_event {TYPE_2__ bpf; TYPE_1__ header; } ;
struct perf_env {int dummy; } ;

/* Variables and functions */
#define  PERF_BPF_EVENT_PROG_LOAD 129 
#define  PERF_BPF_EVENT_PROG_UNLOAD 128 
 scalar_t__ PERF_RECORD_BPF_EVENT ; 
 int /*<<< orphan*/  perf_env__add_bpf_info (struct perf_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int bpf_event__sb_cb(union perf_event *event, void *data)
{
	struct perf_env *env = data;

	if (event->header.type != PERF_RECORD_BPF_EVENT)
		return -1;

	switch (event->bpf.type) {
	case PERF_BPF_EVENT_PROG_LOAD:
		perf_env__add_bpf_info(env, event->bpf.id);

	case PERF_BPF_EVENT_PROG_UNLOAD:
		/*
		 * Do not free bpf_prog_info and btf of the program here,
		 * as annotation still need them. They will be freed at
		 * the end of the session.
		 */
		break;
	default:
		pr_debug("unexpected bpf event type of %d\n", event->bpf.type);
		break;
	}

	return 0;
}