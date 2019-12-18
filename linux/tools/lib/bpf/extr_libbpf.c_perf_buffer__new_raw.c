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
struct perf_buffer_raw_opts {int /*<<< orphan*/  map_keys; int /*<<< orphan*/  cpus; int /*<<< orphan*/  cpu_cnt; int /*<<< orphan*/  ctx; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  attr; } ;
struct perf_buffer_params {int /*<<< orphan*/  map_keys; int /*<<< orphan*/  cpus; int /*<<< orphan*/  cpu_cnt; int /*<<< orphan*/  ctx; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  attr; } ;
struct perf_buffer {int dummy; } ;

/* Variables and functions */
 struct perf_buffer* __perf_buffer__new (int,size_t,struct perf_buffer_params*) ; 

struct perf_buffer *
perf_buffer__new_raw(int map_fd, size_t page_cnt,
		     const struct perf_buffer_raw_opts *opts)
{
	struct perf_buffer_params p = {};

	p.attr = opts->attr;
	p.event_cb = opts->event_cb;
	p.ctx = opts->ctx;
	p.cpu_cnt = opts->cpu_cnt;
	p.cpus = opts->cpus;
	p.map_keys = opts->map_keys;

	return __perf_buffer__new(map_fd, page_cnt, &p);
}