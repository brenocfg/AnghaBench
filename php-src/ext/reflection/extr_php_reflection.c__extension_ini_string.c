#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int module_number; int modifiable; scalar_t__ orig_value; scalar_t__ modified; scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ zend_ini_entry ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int ZEND_INI_ALL ; 
 int ZEND_INI_PERDIR ; 
 int ZEND_INI_SYSTEM ; 
 int ZEND_INI_USER ; 
 char* ZSTR_VAL (scalar_t__) ; 
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  smart_str_appends (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void _extension_ini_string(zend_ini_entry *ini_entry, smart_str *str, char *indent, int number) /* {{{ */
{
	char *comma = "";

	if (number == ini_entry->module_number) {
		smart_str_append_printf(str, "    %sEntry [ %s <", indent, ZSTR_VAL(ini_entry->name));
		if (ini_entry->modifiable == ZEND_INI_ALL) {
			smart_str_appends(str, "ALL");
		} else {
			if (ini_entry->modifiable & ZEND_INI_USER) {
				smart_str_appends(str, "USER");
				comma = ",";
			}
			if (ini_entry->modifiable & ZEND_INI_PERDIR) {
				smart_str_append_printf(str, "%sPERDIR", comma);
				comma = ",";
			}
			if (ini_entry->modifiable & ZEND_INI_SYSTEM) {
				smart_str_append_printf(str, "%sSYSTEM", comma);
			}
		}

		smart_str_appends(str, "> ]\n");
		smart_str_append_printf(str, "    %s  Current = '%s'\n", indent, ini_entry->value ? ZSTR_VAL(ini_entry->value) : "");
		if (ini_entry->modified) {
			smart_str_append_printf(str, "    %s  Default = '%s'\n", indent, ini_entry->orig_value ? ZSTR_VAL(ini_entry->orig_value) : "");
		}
		smart_str_append_printf(str, "    %s}\n", indent);
	}
}