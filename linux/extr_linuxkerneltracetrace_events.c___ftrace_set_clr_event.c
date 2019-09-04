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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int __ftrace_set_clr_event_nolock (struct trace_array*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ftrace_set_clr_event(struct trace_array *tr, const char *match,
				  const char *sub, const char *event, int set)
{
	int ret;

	mutex_lock(&event_mutex);
	ret = __ftrace_set_clr_event_nolock(tr, match, sub, event, set);
	mutex_unlock(&event_mutex);

	return ret;
}