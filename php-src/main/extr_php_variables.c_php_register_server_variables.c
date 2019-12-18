#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {scalar_t__ auth_digest; scalar_t__ auth_password; scalar_t__ auth_user; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* register_server_variables ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 TYPE_2__ SG (int /*<<< orphan*/ ) ; 
 size_t TRACK_VARS_SERVER ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  php_register_variable_quick (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_info ; 
 int /*<<< orphan*/  sapi_get_request_time () ; 
 TYPE_1__ sapi_module ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_dval_to_lval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void php_register_server_variables(void)
{
	zval tmp;
	zval *arr = &PG(http_globals)[TRACK_VARS_SERVER];
	HashTable *ht;

	zval_ptr_dtor_nogc(arr);
	array_init(arr);

	/* Server variables */
	if (sapi_module.register_server_variables) {
		sapi_module.register_server_variables(arr);
	}
	ht = Z_ARRVAL_P(arr);

	/* PHP Authentication support */
	if (SG(request_info).auth_user) {
		ZVAL_STRING(&tmp, SG(request_info).auth_user);
		php_register_variable_quick("PHP_AUTH_USER", sizeof("PHP_AUTH_USER")-1, &tmp, ht);
	}
	if (SG(request_info).auth_password) {
		ZVAL_STRING(&tmp, SG(request_info).auth_password);
		php_register_variable_quick("PHP_AUTH_PW", sizeof("PHP_AUTH_PW")-1, &tmp, ht);
	}
	if (SG(request_info).auth_digest) {
		ZVAL_STRING(&tmp, SG(request_info).auth_digest);
		php_register_variable_quick("PHP_AUTH_DIGEST", sizeof("PHP_AUTH_DIGEST")-1, &tmp, ht);
	}

	/* store request init time */
	ZVAL_DOUBLE(&tmp, sapi_get_request_time());
	php_register_variable_quick("REQUEST_TIME_FLOAT", sizeof("REQUEST_TIME_FLOAT")-1, &tmp, ht);
	ZVAL_LONG(&tmp, zend_dval_to_lval(Z_DVAL(tmp)));
	php_register_variable_quick("REQUEST_TIME", sizeof("REQUEST_TIME")-1, &tmp, ht);
}