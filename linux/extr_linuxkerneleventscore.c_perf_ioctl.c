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
struct file {struct perf_event* private_data; } ;

/* Variables and functions */
 long _perf_ioctl (struct perf_event*,unsigned int,unsigned long) ; 
 struct perf_event_context* perf_event_ctx_lock (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_ctx_unlock (struct perf_event*,struct perf_event_context*) ; 

__attribute__((used)) static long perf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct perf_event *event = file->private_data;
	struct perf_event_context *ctx;
	long ret;

	ctx = perf_event_ctx_lock(event);
	ret = _perf_ioctl(event, cmd, arg);
	perf_event_ctx_unlock(event, ctx);

	return ret;
}