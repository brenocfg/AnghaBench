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
struct event_command {int flags; } ;

/* Variables and functions */
 int EVENT_CMD_FL_NEEDS_REC ; 

__attribute__((used)) static inline bool event_command_needs_rec(struct event_command *cmd_ops)
{
	return cmd_ops->flags & EVENT_CMD_FL_NEEDS_REC;
}