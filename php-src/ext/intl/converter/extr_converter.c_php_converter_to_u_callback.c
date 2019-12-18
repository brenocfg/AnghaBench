#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int param_count; scalar_t__ no_separation; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * params; } ;
struct TYPE_8__ {int /*<<< orphan*/  to_cache; TYPE_3__ to_cb; } ;
typedef  TYPE_1__ php_converter_object ;
typedef  char const* int32_t ;
typedef  int /*<<< orphan*/  UErrorCode ;
struct TYPE_9__ {char const* source; char const* sourceLimit; } ;
typedef  TYPE_2__ UConverterToUnicodeArgs ;
typedef  int /*<<< orphan*/  UConverterCallbackReason ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  U_INTERNAL_PROGRAM_ERROR ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_REFVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_converter_append_toUnicode_target (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  php_converter_throw_failure (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_call_function (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_converter_to_u_callback(const void *context,
                                        UConverterToUnicodeArgs *args,
                                        const char *codeUnits, int32_t length,
                                        UConverterCallbackReason reason,
                                        UErrorCode *pErrorCode) {
	php_converter_object *objval = (php_converter_object*)context;
	zval retval;
	zval zargs[4];

	ZVAL_LONG(&zargs[0], reason);
	if (args->source) {
		ZVAL_STRINGL(&zargs[1], args->source, args->sourceLimit - args->source);
	} else {
		ZVAL_EMPTY_STRING(&zargs[1]);
	}
	if (codeUnits) {
		ZVAL_STRINGL(&zargs[2], codeUnits, length);
	} else {
		ZVAL_EMPTY_STRING(&zargs[2]);
	}
	ZVAL_LONG(&zargs[3], *pErrorCode);

	objval->to_cb.param_count    = 4;
	objval->to_cb.params = zargs;
	objval->to_cb.retval = &retval;
	objval->to_cb.no_separation  = 0;
	if (zend_call_function(&(objval->to_cb), &(objval->to_cache)) == FAILURE) {
		/* Unlikely */
		php_converter_throw_failure(objval, U_INTERNAL_PROGRAM_ERROR, "Unexpected failure calling toUCallback()");
	} else if (!Z_ISUNDEF(retval)) {
		php_converter_append_toUnicode_target(&retval, args, objval);
		zval_ptr_dtor(&retval);
	}

	if (Z_TYPE(zargs[3]) == IS_LONG) {
		*pErrorCode = Z_LVAL(zargs[3]);
	} else if (Z_ISREF(zargs[3]) && Z_TYPE_P(Z_REFVAL(zargs[3])) == IS_LONG) {
		*pErrorCode = Z_LVAL_P(Z_REFVAL(zargs[3]));
	}

	zval_ptr_dtor(&zargs[0]);
	zval_ptr_dtor(&zargs[1]);
	zval_ptr_dtor(&zargs[2]);
	zval_ptr_dtor(&zargs[3]);
}