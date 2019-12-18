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
 struct perf_event_context* perf_event_ctx_lock_nested (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct perf_event_context *
perf_event_ctx_lock(struct perf_event *event)
{
	return perf_event_ctx_lock_nested(event, 0);
}