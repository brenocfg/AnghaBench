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
struct TYPE_5__ {scalar_t__ value; scalar_t__ orig_value; scalar_t__ modified; int /*<<< orphan*/  (* displayer ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ zend_ini_entry ;
struct TYPE_6__ {int /*<<< orphan*/  phpinfo_as_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHPWRITE (char*,size_t) ; 
 int ZEND_INI_DISPLAY_ORIG ; 
 size_t ZSTR_LEN (scalar_t__) ; 
 char* ZSTR_VAL (scalar_t__) ; 
 int /*<<< orphan*/  php_html_puts (char*,size_t) ; 
 TYPE_3__ sapi_module ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void php_ini_displayer_cb(zend_ini_entry *ini_entry, int type)
{
	if (ini_entry->displayer) {
		ini_entry->displayer(ini_entry, type);
	} else {
		char *display_string;
		size_t display_string_length;
		int esc_html=0;

		if (type == ZEND_INI_DISPLAY_ORIG && ini_entry->modified) {
			if (ini_entry->orig_value && ZSTR_VAL(ini_entry->orig_value)[0]) {
				display_string = ZSTR_VAL(ini_entry->orig_value);
				display_string_length = ZSTR_LEN(ini_entry->orig_value);
				esc_html = !sapi_module.phpinfo_as_text;
			} else {
				if (!sapi_module.phpinfo_as_text) {
					display_string = "<i>no value</i>";
					display_string_length = sizeof("<i>no value</i>") - 1;
				} else {
					display_string = "no value";
					display_string_length = sizeof("no value") - 1;
				}
			}
		} else if (ini_entry->value && ZSTR_VAL(ini_entry->value)[0]) {
			display_string = ZSTR_VAL(ini_entry->value);
			display_string_length = ZSTR_LEN(ini_entry->value);
			esc_html = !sapi_module.phpinfo_as_text;
		} else {
			if (!sapi_module.phpinfo_as_text) {
				display_string = "<i>no value</i>";
				display_string_length = sizeof("<i>no value</i>") - 1;
			} else {
				display_string = "no value";
				display_string_length = sizeof("no value") - 1;
			}
		}

		if (esc_html) {
			php_html_puts(display_string, display_string_length);
		} else {
			PHPWRITE(display_string, display_string_length);
		}
	}
}