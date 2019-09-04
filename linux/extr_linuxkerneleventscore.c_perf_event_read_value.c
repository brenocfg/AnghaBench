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
struct perf_event_context {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_read_value (struct perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct perf_event_context* perf_event_ctx_lock (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_ctx_unlock (struct perf_event*,struct perf_event_context*) ; 

u64 perf_event_read_value(struct perf_event *event, u64 *enabled, u64 *running)
{
	struct perf_event_context *ctx;
	u64 count;

	ctx = perf_event_ctx_lock(event);
	count = __perf_event_read_value(event, enabled, running);
	perf_event_ctx_unlock(event, ctx);

	return count;
}