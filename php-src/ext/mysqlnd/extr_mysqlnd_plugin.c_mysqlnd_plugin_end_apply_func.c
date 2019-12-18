#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {int /*<<< orphan*/  (* plugin_shutdown ) (struct st_mysqlnd_plugin_header*) ;} ;
struct st_mysqlnd_plugin_header {TYPE_1__ m; } ;

/* Variables and functions */
 int ZEND_HASH_APPLY_REMOVE ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct st_mysqlnd_plugin_header*) ; 

int
mysqlnd_plugin_end_apply_func(zval *el)
{
	struct st_mysqlnd_plugin_header * plugin_header = (struct st_mysqlnd_plugin_header *)Z_PTR_P(el);
	if (plugin_header->m.plugin_shutdown) {
		plugin_header->m.plugin_shutdown(plugin_header);
	}
	return ZEND_HASH_APPLY_REMOVE;
}