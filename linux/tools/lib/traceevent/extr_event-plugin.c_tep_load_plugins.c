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
struct tep_plugin_list {int dummy; } ;
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  load_plugin ; 
 int /*<<< orphan*/  load_plugins (struct tep_handle*,char*,int /*<<< orphan*/ ,struct tep_plugin_list**) ; 

struct tep_plugin_list*
tep_load_plugins(struct tep_handle *tep)
{
	struct tep_plugin_list *list = NULL;

	load_plugins(tep, ".so", load_plugin, &list);
	return list;
}