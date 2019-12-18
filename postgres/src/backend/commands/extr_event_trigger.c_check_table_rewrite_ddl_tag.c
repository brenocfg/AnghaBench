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
typedef  int /*<<< orphan*/  event_trigger_command_tag_check_result ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TRIGGER_COMMAND_TAG_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVENT_TRIGGER_COMMAND_TAG_OK ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

__attribute__((used)) static event_trigger_command_tag_check_result
check_table_rewrite_ddl_tag(const char *tag)
{
	if (pg_strcasecmp(tag, "ALTER TABLE") == 0 ||
		pg_strcasecmp(tag, "ALTER TYPE") == 0)
		return EVENT_TRIGGER_COMMAND_TAG_OK;

	return EVENT_TRIGGER_COMMAND_TAG_NOT_SUPPORTED;
}