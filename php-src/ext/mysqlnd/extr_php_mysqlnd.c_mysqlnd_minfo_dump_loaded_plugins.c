#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct st_mysqlnd_plugin_header {scalar_t__ plugin_name; } ;
struct TYPE_4__ {scalar_t__ s; } ;
typedef  TYPE_1__ smart_str ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int
mysqlnd_minfo_dump_loaded_plugins(zval *el, void * buf)
{
	smart_str * buffer = (smart_str *) buf;
	struct st_mysqlnd_plugin_header * plugin_header = (struct st_mysqlnd_plugin_header *)Z_PTR_P(el);
	if (plugin_header->plugin_name) {
		if (buffer->s) {
			smart_str_appendc(buffer, ',');
		}
		smart_str_appends(buffer, plugin_header->plugin_name);
	}
	return ZEND_HASH_APPLY_KEEP;
}