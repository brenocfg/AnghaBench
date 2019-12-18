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
struct event_trigger_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_EVENT_STR ; 
 int /*<<< orphan*/  ENABLE_HIST_STR ; 
 struct event_trigger_ops event_disable_count_trigger_ops ; 
 struct event_trigger_ops event_disable_trigger_ops ; 
 struct event_trigger_ops event_enable_count_trigger_ops ; 
 struct event_trigger_ops event_enable_trigger_ops ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct event_trigger_ops *
event_enable_get_trigger_ops(char *cmd, char *param)
{
	struct event_trigger_ops *ops;
	bool enable;

#ifdef CONFIG_HIST_TRIGGERS
	enable = ((strcmp(cmd, ENABLE_EVENT_STR) == 0) ||
		  (strcmp(cmd, ENABLE_HIST_STR) == 0));
#else
	enable = strcmp(cmd, ENABLE_EVENT_STR) == 0;
#endif
	if (enable)
		ops = param ? &event_enable_count_trigger_ops :
			&event_enable_trigger_ops;
	else
		ops = param ? &event_disable_count_trigger_ops :
			&event_disable_trigger_ops;

	return ops;
}