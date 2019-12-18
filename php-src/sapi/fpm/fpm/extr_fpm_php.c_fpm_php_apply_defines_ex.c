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
struct key_value_s {char* key; char* value; } ;
typedef  char* PG ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_TRUE ; 
 int /*<<< orphan*/  MODULE_PERSISTENT ; 
 int /*<<< orphan*/  PHP_INI_STAGE_ACTIVATE ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_php_disable (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_php_zend_ini_alter_master (char*,int,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_dl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zend_disable_class ; 
 int /*<<< orphan*/  zend_disable_function ; 

int fpm_php_apply_defines_ex(struct key_value_s *kv, int mode) /* {{{ */
{

	char *name = kv->key;
	char *value = kv->value;
	int name_len = strlen(name);
	int value_len = strlen(value);

	if (!strcmp(name, "extension") && *value) {
		zval zv;
		php_dl(value, MODULE_PERSISTENT, &zv, 1);
		return Z_TYPE(zv) == IS_TRUE;
	}

	if (fpm_php_zend_ini_alter_master(name, name_len, value, value_len, mode, PHP_INI_STAGE_ACTIVATE) == FAILURE) {
		return -1;
	}

	if (!strcmp(name, "disable_functions") && *value) {
		char *v = strdup(value);
		PG(disable_functions) = v;
		fpm_php_disable(v, zend_disable_function);
		return 1;
	}

	if (!strcmp(name, "disable_classes") && *value) {
		char *v = strdup(value);
		PG(disable_classes) = v;
		fpm_php_disable(v, zend_disable_class);
		return 1;
	}

	return 1;
}