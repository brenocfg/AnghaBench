#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/  name; scalar_t__ version; int /*<<< orphan*/  (* info_func ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ zend_module_entry ;
struct TYPE_6__ {int /*<<< orphan*/  phpinfo_as_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_INI_ENTRIES () ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_info_print_table_end () ; 
 int /*<<< orphan*/  php_info_print_table_header (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_info_print_table_row (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  php_info_print_table_start () ; 
 int /*<<< orphan*/  php_info_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  php_strtolower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_url_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ sapi_module ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void php_info_print_module(zend_module_entry *zend_module) /* {{{ */
{
	if (zend_module->info_func || zend_module->version) {
		if (!sapi_module.phpinfo_as_text) {
			zend_string *url_name = php_url_encode(zend_module->name, strlen(zend_module->name));

			php_strtolower(ZSTR_VAL(url_name), ZSTR_LEN(url_name));
			php_info_printf("<h2><a name=\"module_%s\">%s</a></h2>\n", ZSTR_VAL(url_name), zend_module->name);

			efree(url_name);
		} else {
			php_info_print_table_start();
			php_info_print_table_header(1, zend_module->name);
			php_info_print_table_end();
		}
		if (zend_module->info_func) {
			zend_module->info_func(zend_module);
		} else {
			php_info_print_table_start();
			php_info_print_table_row(2, "Version", zend_module->version);
			php_info_print_table_end();
			DISPLAY_INI_ENTRIES();
		}
	} else {
		if (!sapi_module.phpinfo_as_text) {
			php_info_printf("<tr><td class=\"v\">%s</td></tr>\n", zend_module->name);
		} else {
			php_info_printf("%s\n", zend_module->name);
		}
	}
}