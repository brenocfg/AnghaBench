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
 int /*<<< orphan*/  _perf_event_enable (struct perf_event*) ; 
 struct perf_event_context* perf_event_ctx_lock (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_ctx_unlock (struct perf_event*,struct perf_event_context*) ; 

void perf_event_enable(struct perf_event *event)
{
	struct perf_event_context *ctx;

	ctx = perf_event_ctx_lock(event);
	_perf_event_enable(event);
	perf_event_ctx_unlock(event, ctx);
}