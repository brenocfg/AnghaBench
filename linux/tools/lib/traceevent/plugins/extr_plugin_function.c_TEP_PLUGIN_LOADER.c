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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  function_handler ; 
 int /*<<< orphan*/  plugin_options ; 
 int /*<<< orphan*/  tep_plugin_add_options (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_register_event_handler (struct tep_handle*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int TEP_PLUGIN_LOADER(struct tep_handle *tep)
{
	tep_register_event_handler(tep, -1, "ftrace", "function",
				   function_handler, NULL);

	tep_plugin_add_options("ftrace", plugin_options);

	return 0;
}