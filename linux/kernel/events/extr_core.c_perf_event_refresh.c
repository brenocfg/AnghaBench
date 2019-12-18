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
struct perf_event_context {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int _perf_event_refresh (struct perf_event*,int) ; 
 struct perf_event_context* perf_event_ctx_lock (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_ctx_unlock (struct perf_event*,struct perf_event_context*) ; 

int perf_event_refresh(struct perf_event *event, int refresh)
{
	struct perf_event_context *ctx;
	int ret;

	ctx = perf_event_ctx_lock(event);
	ret = _perf_event_refresh(event, refresh);
	perf_event_ctx_unlock(event, ctx);

	return ret;
}