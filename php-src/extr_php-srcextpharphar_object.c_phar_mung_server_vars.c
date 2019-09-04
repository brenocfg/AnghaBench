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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 int PHAR_G (int /*<<< orphan*/ ) ; 
 int PHAR_MUNG_PHP_SELF ; 
 int PHAR_MUNG_REQUEST_URI ; 
 int PHAR_MUNG_SCRIPT_FILENAME ; 
 int PHAR_MUNG_SCRIPT_NAME ; 
 size_t TRACK_VARS_SERVER ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * Z_ARRVAL (int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  phar_SERVER_mung_list ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/ * strpprintf (int,char*,char*,char*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phar_mung_server_vars(char *fname, char *entry, size_t entry_len, char *basename, size_t request_uri_len) /* {{{ */
{
	HashTable *_SERVER;
	zval *stuff;
	char *path_info;
	size_t basename_len = strlen(basename);
	size_t code;
	zval temp;

	/* "tweak" $_SERVER variables requested in earlier call to Phar::mungServer() */
	if (Z_TYPE(PG(http_globals)[TRACK_VARS_SERVER]) == IS_UNDEF) {
		return;
	}

	_SERVER = Z_ARRVAL(PG(http_globals)[TRACK_VARS_SERVER]);

	/* PATH_INFO and PATH_TRANSLATED should always be munged */
	if (NULL != (stuff = zend_hash_str_find(_SERVER, "PATH_INFO", sizeof("PATH_INFO")-1))) {
		path_info = Z_STRVAL_P(stuff);
		code = Z_STRLEN_P(stuff);
		if (code > (size_t)entry_len && !memcmp(path_info, entry, entry_len)) {
			ZVAL_STR(&temp, Z_STR_P(stuff));
			ZVAL_STRINGL(stuff, path_info + entry_len, request_uri_len);
			zend_hash_str_update(_SERVER, "PHAR_PATH_INFO", sizeof("PHAR_PATH_INFO")-1, &temp);
		}
	}

	if (NULL != (stuff = zend_hash_str_find(_SERVER, "PATH_TRANSLATED", sizeof("PATH_TRANSLATED")-1))) {
		zend_string *str = strpprintf(4096, "phar://%s%s", fname, entry);

		ZVAL_STR(&temp, Z_STR_P(stuff));
		ZVAL_NEW_STR(stuff, str);

		zend_hash_str_update(_SERVER, "PHAR_PATH_TRANSLATED", sizeof("PHAR_PATH_TRANSLATED")-1, &temp);
	}

	if (!PHAR_G(phar_SERVER_mung_list)) {
		return;
	}

	if (PHAR_G(phar_SERVER_mung_list) & PHAR_MUNG_REQUEST_URI) {
		if (NULL != (stuff = zend_hash_str_find(_SERVER, "REQUEST_URI", sizeof("REQUEST_URI")-1))) {
			path_info = Z_STRVAL_P(stuff);
			code = Z_STRLEN_P(stuff);
			if (code > basename_len && !memcmp(path_info, basename, basename_len)) {
				ZVAL_STR(&temp, Z_STR_P(stuff));
				ZVAL_STRINGL(stuff, path_info + basename_len, code - basename_len);
				zend_hash_str_update(_SERVER, "PHAR_REQUEST_URI", sizeof("PHAR_REQUEST_URI")-1, &temp);
			}
		}
	}

	if (PHAR_G(phar_SERVER_mung_list) & PHAR_MUNG_PHP_SELF) {
		if (NULL != (stuff = zend_hash_str_find(_SERVER, "PHP_SELF", sizeof("PHP_SELF")-1))) {
			path_info = Z_STRVAL_P(stuff);
			code = Z_STRLEN_P(stuff);

			if (code > basename_len && !memcmp(path_info, basename, basename_len)) {
				ZVAL_STR(&temp, Z_STR_P(stuff));
				ZVAL_STRINGL(stuff, path_info + basename_len, code - basename_len);
				zend_hash_str_update(_SERVER, "PHAR_PHP_SELF", sizeof("PHAR_PHP_SELF")-1, &temp);
			}
		}
	}

	if (PHAR_G(phar_SERVER_mung_list) & PHAR_MUNG_SCRIPT_NAME) {
		if (NULL != (stuff = zend_hash_str_find(_SERVER, "SCRIPT_NAME", sizeof("SCRIPT_NAME")-1))) {
			ZVAL_STR(&temp, Z_STR_P(stuff));
			ZVAL_STRINGL(stuff, entry, entry_len);
			zend_hash_str_update(_SERVER, "PHAR_SCRIPT_NAME", sizeof("PHAR_SCRIPT_NAME")-1, &temp);
		}
	}

	if (PHAR_G(phar_SERVER_mung_list) & PHAR_MUNG_SCRIPT_FILENAME) {
		if (NULL != (stuff = zend_hash_str_find(_SERVER, "SCRIPT_FILENAME", sizeof("SCRIPT_FILENAME")-1))) {
			zend_string *str = strpprintf(4096, "phar://%s%s", fname, entry);

			ZVAL_STR(&temp, Z_STR_P(stuff));
			ZVAL_NEW_STR(stuff, str);

			zend_hash_str_update(_SERVER, "PHAR_SCRIPT_FILENAME", sizeof("PHAR_SCRIPT_FILENAME")-1, &temp);
		}
	}
}