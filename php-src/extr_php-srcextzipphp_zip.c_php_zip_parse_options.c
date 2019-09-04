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
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTICE ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ IS_STRING ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_zip_parse_options(zval *options, zend_long *remove_all_path, char **remove_path, size_t *remove_path_len, char **add_path, size_t *add_path_len) /* {{{ */
{
	zval *option;
	if ((option = zend_hash_str_find(Z_ARRVAL_P(options), "remove_all_path", sizeof("remove_all_path") - 1)) != NULL) {
		*remove_all_path = zval_get_long(option);
	}

	/* If I add more options, it would make sense to create a nice static struct and loop over it. */
	if ((option = zend_hash_str_find(Z_ARRVAL_P(options), "remove_path", sizeof("remove_path") - 1)) != NULL) {
		if (Z_TYPE_P(option) != IS_STRING) {
			php_error_docref(NULL, E_WARNING, "remove_path option expected to be a string");
			return -1;
		}

		if (Z_STRLEN_P(option) < 1) {
			php_error_docref(NULL, E_NOTICE, "Empty string given as remove_path option");
			return -1;
		}

		if (Z_STRLEN_P(option) >= MAXPATHLEN) {
			php_error_docref(NULL, E_WARNING, "remove_path string is too long (max: %d, %zd given)",
						MAXPATHLEN - 1, Z_STRLEN_P(option));
			return -1;
		}
		*remove_path_len = Z_STRLEN_P(option);
		*remove_path = Z_STRVAL_P(option);
	}

	if ((option = zend_hash_str_find(Z_ARRVAL_P(options), "add_path", sizeof("add_path") - 1)) != NULL) {
		if (Z_TYPE_P(option) != IS_STRING) {
			php_error_docref(NULL, E_WARNING, "add_path option expected to be a string");
			return -1;
		}

		if (Z_STRLEN_P(option) < 1) {
			php_error_docref(NULL, E_NOTICE, "Empty string given as the add_path option");
			return -1;
		}

		if (Z_STRLEN_P(option) >= MAXPATHLEN) {
			php_error_docref(NULL, E_WARNING, "add_path string too long (max: %d, %zd given)",
						MAXPATHLEN - 1, Z_STRLEN_P(option));
			return -1;
		}
		*add_path_len = Z_STRLEN_P(option);
		*add_path = Z_STRVAL_P(option);
	}
	return 1;
}