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
struct perf_event_attr {int sample_period; int wakeup_events; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  type; int /*<<< orphan*/  config; int /*<<< orphan*/  member_0; } ;
struct perf_buffer_params {int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * lost_cb; int /*<<< orphan*/ * sample_cb; struct perf_event_attr* attr; } ;
struct perf_buffer_opts {int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * lost_cb; int /*<<< orphan*/ * sample_cb; } ;
struct perf_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_BPF_OUTPUT ; 
 int /*<<< orphan*/  PERF_SAMPLE_RAW ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 struct perf_buffer* __perf_buffer__new (int,size_t,struct perf_buffer_params*) ; 

struct perf_buffer *perf_buffer__new(int map_fd, size_t page_cnt,
				     const struct perf_buffer_opts *opts)
{
	struct perf_buffer_params p = {};
	struct perf_event_attr attr = { 0, };

	attr.config = PERF_COUNT_SW_BPF_OUTPUT,
	attr.type = PERF_TYPE_SOFTWARE;
	attr.sample_type = PERF_SAMPLE_RAW;
	attr.sample_period = 1;
	attr.wakeup_events = 1;

	p.attr = &attr;
	p.sample_cb = opts ? opts->sample_cb : NULL;
	p.lost_cb = opts ? opts->lost_cb : NULL;
	p.ctx = opts ? opts->ctx : NULL;

	return __perf_buffer__new(map_fd, page_cnt, &p);
}