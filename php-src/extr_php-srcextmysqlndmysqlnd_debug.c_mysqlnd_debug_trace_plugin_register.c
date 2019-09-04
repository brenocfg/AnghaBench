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
struct st_mysqlnd_plugin_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mysqlnd_plugin_register_ex (struct st_mysqlnd_plugin_header*) ; 
 int /*<<< orphan*/  mysqlnd_plugin_trace_log_plugin ; 

void
mysqlnd_debug_trace_plugin_register(void)
{
	mysqlnd_plugin_register_ex((struct st_mysqlnd_plugin_header *) &mysqlnd_plugin_trace_log_plugin);
}