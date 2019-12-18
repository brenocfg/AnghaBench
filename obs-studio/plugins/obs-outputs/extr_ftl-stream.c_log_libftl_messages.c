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
typedef  int /*<<< orphan*/  ftl_log_severity_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void log_libftl_messages(ftl_log_severity_t log_level,
				const char *message)
{
	UNUSED_PARAMETER(log_level);
	blog(LOG_WARNING, "[libftl] %s", message);
}