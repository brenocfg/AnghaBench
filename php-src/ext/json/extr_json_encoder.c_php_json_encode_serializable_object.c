#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int /*<<< orphan*/  smart_str ;
struct TYPE_8__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_2__ php_json_encoder ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 scalar_t__ GC_IS_RECURSIVE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_OBJECT ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  PHP_JSON_ERROR_RECURSION ; 
 int /*<<< orphan*/  PHP_JSON_HASH_PROTECT_RECURSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_JSON_HASH_UNPROTECT_RECURSION (int /*<<< orphan*/ *) ; 
 int PHP_JSON_PARTIAL_OUTPUT_ON_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Z_OBJ (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_OBJPROP_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int php_json_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int php_json_encode_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_json_encode_serializable_object(smart_str *buf, zval *val, int options, php_json_encoder *encoder) /* {{{ */
{
	zend_class_entry *ce = Z_OBJCE_P(val);
	HashTable* myht = Z_OBJPROP_P(val);
	zval retval, fname;
	int return_code;

	if (myht && GC_IS_RECURSIVE(myht)) {
		encoder->error_code = PHP_JSON_ERROR_RECURSION;
		if (options & PHP_JSON_PARTIAL_OUTPUT_ON_ERROR) {
			smart_str_appendl(buf, "null", 4);
		}
		return FAILURE;
	}

	PHP_JSON_HASH_PROTECT_RECURSION(myht);

	ZVAL_STRING(&fname, "jsonSerialize");

	if (FAILURE == call_user_function(NULL, val, &fname, &retval, 0, NULL) || Z_TYPE(retval) == IS_UNDEF) {
		if (!EG(exception)) {
			zend_throw_exception_ex(NULL, 0, "Failed calling %s::jsonSerialize()", ZSTR_VAL(ce->name));
		}
		zval_ptr_dtor(&fname);

		if (options & PHP_JSON_PARTIAL_OUTPUT_ON_ERROR) {
			smart_str_appendl(buf, "null", 4);
		}
		PHP_JSON_HASH_UNPROTECT_RECURSION(myht);
		return FAILURE;
	}

	if (EG(exception)) {
		/* Error already raised */
		zval_ptr_dtor(&retval);
		zval_ptr_dtor(&fname);

		if (options & PHP_JSON_PARTIAL_OUTPUT_ON_ERROR) {
			smart_str_appendl(buf, "null", 4);
		}
		PHP_JSON_HASH_UNPROTECT_RECURSION(myht);
		return FAILURE;
	}

	if ((Z_TYPE(retval) == IS_OBJECT) &&
		(Z_OBJ(retval) == Z_OBJ_P(val))) {
		/* Handle the case where jsonSerialize does: return $this; by going straight to encode array */
		PHP_JSON_HASH_UNPROTECT_RECURSION(myht);
		return_code = php_json_encode_array(buf, &retval, options, encoder);
	} else {
		/* All other types, encode as normal */
		return_code = php_json_encode_zval(buf, &retval, options, encoder);
		PHP_JSON_HASH_UNPROTECT_RECURSION(myht);
	}

	zval_ptr_dtor(&retval);
	zval_ptr_dtor(&fname);

	return return_code;
}