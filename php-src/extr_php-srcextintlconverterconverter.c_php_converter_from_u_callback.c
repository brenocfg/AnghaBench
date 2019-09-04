#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int param_count; scalar_t__ no_separation; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * params; } ;
struct TYPE_5__ {int /*<<< orphan*/  from_cache; TYPE_2__ from_cb; } ;
typedef  TYPE_1__ php_converter_object ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UConverterFromUnicodeArgs ;
typedef  int /*<<< orphan*/  UConverterCallbackReason ;
typedef  int /*<<< orphan*/  UChar32 ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  U16_NEXT (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_INTERNAL_PROGRAM_ERROR ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_REFVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_converter_append_fromUnicode_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  php_converter_throw_failure (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_call_function (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_converter_from_u_callback(const void *context,
                                          UConverterFromUnicodeArgs *args,
                                          const UChar *codeUnits, int32_t length, UChar32 codePoint,
                                          UConverterCallbackReason reason,
                                          UErrorCode *pErrorCode) {
	php_converter_object *objval = (php_converter_object*)context;
	zval retval;
	zval zargs[4];
	int i;

	ZVAL_LONG(&zargs[0], reason);
	array_init(&zargs[1]);
	i = 0;
	while (i < length) {
		UChar32 c;
		U16_NEXT(codeUnits, i, length, c);
		add_next_index_long(&zargs[1], c);
	}
	ZVAL_LONG(&zargs[2], codePoint);
	ZVAL_LONG(&zargs[3], *pErrorCode);

	objval->from_cb.param_count = 4;
	objval->from_cb.params = zargs;
	objval->from_cb.retval = &retval;
	objval->from_cb.no_separation  = 0;
	if (zend_call_function(&(objval->from_cb), &(objval->from_cache)) == FAILURE) {
		/* Unlikely */
		php_converter_throw_failure(objval, U_INTERNAL_PROGRAM_ERROR, "Unexpected failure calling fromUCallback()");
	} else if (!Z_ISUNDEF(retval)) {
		php_converter_append_fromUnicode_target(&retval, args, objval);
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