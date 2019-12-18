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
typedef  int /*<<< orphan*/  zend_string ;
typedef  scalar_t__ zend_off_t ;
typedef  int /*<<< orphan*/  zend_fcall_info_cache ;
struct TYPE_4__ {int param_count; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * params; } ;
typedef  TYPE_1__ zend_fcall_info ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_FALSE 130 
#define  IS_LONG 129 
#define  IS_TRUE 128 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NEW_REF (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ZVAL_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_DELREF (int /*<<< orphan*/ ) ; 
 int Z_LVAL (int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 char* estrndup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * php_stream_copy_to_mem (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_rewind (int /*<<< orphan*/ *) ; 
 int zend_call_function (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zend_fcall_info_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_call_openssl_signverify(int is_sign, php_stream *fp, zend_off_t end, char *key, size_t key_len, char **signature, size_t *signature_len) /* {{{ */
{
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval retval, zp[3], openssl;
	zend_string *str;

	ZVAL_STRINGL(&openssl, is_sign ? "openssl_sign" : "openssl_verify", is_sign ? sizeof("openssl_sign")-1 : sizeof("openssl_verify")-1);
	ZVAL_STRINGL(&zp[1], *signature, *signature_len);
	ZVAL_STRINGL(&zp[2], key, key_len);
	php_stream_rewind(fp);
	str = php_stream_copy_to_mem(fp, (size_t) end, 0);
	if (str) {
		ZVAL_STR(&zp[0], str);
	} else {
		ZVAL_EMPTY_STRING(&zp[0]);
	}

	if ((size_t)end != Z_STRLEN(zp[0])) {
		zval_ptr_dtor_str(&zp[0]);
		zval_ptr_dtor_str(&zp[1]);
		zval_ptr_dtor_str(&zp[2]);
		zval_ptr_dtor_str(&openssl);
		return FAILURE;
	}

	if (FAILURE == zend_fcall_info_init(&openssl, 0, &fci, &fcc, NULL, NULL)) {
		zval_ptr_dtor_str(&zp[0]);
		zval_ptr_dtor_str(&zp[1]);
		zval_ptr_dtor_str(&zp[2]);
		zval_ptr_dtor_str(&openssl);
		return FAILURE;
	}

	fci.param_count = 3;
	fci.params = zp;
	Z_ADDREF(zp[0]);
	if (is_sign) {
		ZVAL_NEW_REF(&zp[1], &zp[1]);
	} else {
		Z_ADDREF(zp[1]);
	}
	Z_ADDREF(zp[2]);

	fci.retval = &retval;

	if (FAILURE == zend_call_function(&fci, &fcc)) {
		zval_ptr_dtor_str(&zp[0]);
		zval_ptr_dtor(&zp[1]);
		zval_ptr_dtor_str(&zp[2]);
		zval_ptr_dtor_str(&openssl);
		return FAILURE;
	}

	zval_ptr_dtor_str(&openssl);
	Z_DELREF(zp[0]);

	if (is_sign) {
		ZVAL_UNREF(&zp[1]);
	} else {
		Z_DELREF(zp[1]);
	}
	Z_DELREF(zp[2]);

	zval_ptr_dtor_str(&zp[0]);
	zval_ptr_dtor_str(&zp[2]);

	switch (Z_TYPE(retval)) {
		default:
		case IS_LONG:
			zval_ptr_dtor(&zp[1]);
			if (1 == Z_LVAL(retval)) {
				return SUCCESS;
			}
			return FAILURE;
		case IS_TRUE:
			*signature = estrndup(Z_STRVAL(zp[1]), Z_STRLEN(zp[1]));
			*signature_len = Z_STRLEN(zp[1]);
			zval_ptr_dtor(&zp[1]);
			return SUCCESS;
		case IS_FALSE:
			zval_ptr_dtor(&zp[1]);
			return FAILURE;
	}
}