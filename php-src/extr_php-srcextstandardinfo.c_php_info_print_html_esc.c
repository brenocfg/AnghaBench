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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  ENT_QUOTES ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_escape_html_entities (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t php_output_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_info_print_html_esc(const char *str, size_t len) /* {{{ */
{
	size_t written;
	zend_string *new_str;

	new_str = php_escape_html_entities((unsigned char *) str, len, 0, ENT_QUOTES, "utf-8");
	written = php_output_write(ZSTR_VAL(new_str), ZSTR_LEN(new_str));
	zend_string_free(new_str);
	return written;
}