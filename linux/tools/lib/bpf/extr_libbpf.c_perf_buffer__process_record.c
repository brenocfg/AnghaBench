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
struct perf_sample_raw {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct perf_sample_lost {int /*<<< orphan*/  lost; } ;
struct perf_event_header {int type; } ;
struct perf_cpu_buf {int /*<<< orphan*/  cpu; struct perf_buffer* pb; } ;
struct perf_buffer {int (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event_header*) ;int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* lost_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sample_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum bpf_perf_event_ret { ____Placeholder_bpf_perf_event_ret } bpf_perf_event_ret ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int LIBBPF_PERF_EVENT_ERROR ; 
#define  PERF_RECORD_LOST 129 
#define  PERF_RECORD_SAMPLE 128 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event_header*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bpf_perf_event_ret
perf_buffer__process_record(struct perf_event_header *e, void *ctx)
{
	struct perf_cpu_buf *cpu_buf = ctx;
	struct perf_buffer *pb = cpu_buf->pb;
	void *data = e;

	/* user wants full control over parsing perf event */
	if (pb->event_cb)
		return pb->event_cb(pb->ctx, cpu_buf->cpu, e);

	switch (e->type) {
	case PERF_RECORD_SAMPLE: {
		struct perf_sample_raw *s = data;

		if (pb->sample_cb)
			pb->sample_cb(pb->ctx, cpu_buf->cpu, s->data, s->size);
		break;
	}
	case PERF_RECORD_LOST: {
		struct perf_sample_lost *s = data;

		if (pb->lost_cb)
			pb->lost_cb(pb->ctx, cpu_buf->cpu, s->lost);
		break;
	}
	default:
		pr_warning("unknown perf sample type %d\n", e->type);
		return LIBBPF_PERF_EVENT_ERROR;
	}
	return LIBBPF_PERF_EVENT_CONT;
}