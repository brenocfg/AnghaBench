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

/* Variables and functions */
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

bool
variable_is_guc_list_quote(const char *name)
{
	if (pg_strcasecmp(name, "temp_tablespaces") == 0 ||
		pg_strcasecmp(name, "session_preload_libraries") == 0 ||
		pg_strcasecmp(name, "shared_preload_libraries") == 0 ||
		pg_strcasecmp(name, "local_preload_libraries") == 0 ||
		pg_strcasecmp(name, "search_path") == 0)
		return true;
	else
		return false;
}