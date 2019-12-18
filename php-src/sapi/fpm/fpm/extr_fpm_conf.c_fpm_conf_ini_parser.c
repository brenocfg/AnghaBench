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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
#define  ZEND_INI_PARSER_ENTRY 130 
#define  ZEND_INI_PARSER_POP_ENTRY 129 
#define  ZEND_INI_PARSER_SECTION 128 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  fpm_conf_ini_parser_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fpm_conf_ini_parser_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fpm_conf_ini_parser_section (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ini_filename ; 
 int /*<<< orphan*/  ini_lineno ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpm_conf_ini_parser(zval *arg1, zval *arg2, zval *arg3, int callback_type, void *arg) /* {{{ */
{
	int *error;

	if (!arg1 || !arg) return;
	error = (int *)arg;
	if (*error) return; /* We got already an error. Switch to the end. */

	switch(callback_type) {
		case ZEND_INI_PARSER_ENTRY:
			fpm_conf_ini_parser_entry(arg1, arg2, error);
			break;
		case ZEND_INI_PARSER_SECTION:
			fpm_conf_ini_parser_section(arg1, error);
			break;
		case ZEND_INI_PARSER_POP_ENTRY:
			fpm_conf_ini_parser_array(arg1, arg3, arg2, error);
			break;
		default:
			zlog(ZLOG_ERROR, "[%s:%d] Unknown INI syntax", ini_filename, ini_lineno);
			*error = 1;
			break;
	}
}