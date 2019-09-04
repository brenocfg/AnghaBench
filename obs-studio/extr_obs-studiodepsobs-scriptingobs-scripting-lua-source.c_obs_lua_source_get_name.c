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
struct obs_lua_source {char const* display_name; } ;

/* Variables and functions */

__attribute__((used)) static const char *obs_lua_source_get_name(void *type_data)
{
	struct obs_lua_source *ls = type_data;
	return ls->display_name;
}