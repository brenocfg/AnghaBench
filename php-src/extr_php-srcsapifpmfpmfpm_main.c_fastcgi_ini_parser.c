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
struct key_value_s {char* key; char* value; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int ZEND_INI_PARSER_ENTRY ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int fpm_php_apply_defines_ex (struct key_value_s*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void fastcgi_ini_parser(zval *arg1, zval *arg2, zval *arg3, int callback_type, void *arg) /* {{{ */
{
	int *mode = (int *)arg;
	char *key;
	char *value = NULL;
	struct key_value_s kv;

	if (!mode || !arg1) return;

	if (callback_type != ZEND_INI_PARSER_ENTRY) {
		zlog(ZLOG_ERROR, "Passing INI directive through FastCGI: only classic entries are allowed");
		return;
	}

	key = Z_STRVAL_P(arg1);

	if (!key || strlen(key) < 1) {
		zlog(ZLOG_ERROR, "Passing INI directive through FastCGI: empty key");
		return;
	}

	if (arg2) {
		value = Z_STRVAL_P(arg2);
	}

	if (!value) {
		zlog(ZLOG_ERROR, "Passing INI directive through FastCGI: empty value for key '%s'", key);
		return;
	}

	kv.key = key;
	kv.value = value;
	kv.next = NULL;
	if (fpm_php_apply_defines_ex(&kv, *mode) == -1) {
		zlog(ZLOG_ERROR, "Passing INI directive through FastCGI: unable to set '%s'", key);
	}
}