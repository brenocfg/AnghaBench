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
typedef  int /*<<< orphan*/  zend_fcall_info_cache ;
struct TYPE_4__ {int /*<<< orphan*/  function_name; } ;
typedef  TYPE_1__ zend_fcall_info ;
typedef  int /*<<< orphan*/  php_converter_object ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  U_INTERNAL_PROGRAM_ERROR ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_index_string (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_converter_throw_failure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  zend_array_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ zend_fcall_info_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static void php_converter_resolve_callback(zval *zobj,
                                           php_converter_object *objval,
                                           const char *callback_name,
                                           zend_fcall_info *finfo,
                                           zend_fcall_info_cache *fcache) {
	char *errstr = NULL;
	zval caller;

	array_init(&caller);
	Z_ADDREF_P(zobj);
	add_index_zval(&caller, 0, zobj);
	add_index_string(&caller, 1, callback_name);
	if (zend_fcall_info_init(&caller, 0, finfo, fcache, NULL, &errstr) == FAILURE) {
		php_converter_throw_failure(objval, U_INTERNAL_PROGRAM_ERROR, "Error setting converter callback: %s", errstr);
	}
	zend_array_destroy(Z_ARR(caller));
	ZVAL_UNDEF(&finfo->function_name);
	if (errstr) {
		efree(errstr);
	}
}