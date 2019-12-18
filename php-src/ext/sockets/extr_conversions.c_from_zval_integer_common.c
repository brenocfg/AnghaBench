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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_5__ {int has_error; } ;
struct TYPE_6__ {TYPE_1__ err; } ;
typedef  TYPE_2__ ser_context ;

/* Variables and functions */
#define  IS_DOUBLE 131 
#define  IS_LONG 130 
#define  IS_OBJECT 129 
#define  IS_STRING 128 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/  const*) ; 
 int Z_TYPE_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  convert_to_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_from_zval_err (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  is_numeric_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_long from_zval_integer_common(const zval *arr_value, ser_context *ctx)
{
	zend_long ret = 0;
	zval lzval;

	ZVAL_NULL(&lzval);
	if (Z_TYPE_P(arr_value) != IS_LONG) {
		ZVAL_COPY(&lzval, (zval *)arr_value);
		arr_value = &lzval;
	}

	switch (Z_TYPE_P(arr_value)) {
	case IS_LONG:
long_case:
		ret = Z_LVAL_P(arr_value);
		break;

	/* if not long we're operating on lzval */
	case IS_DOUBLE:
double_case:
		convert_to_long(&lzval);
		goto long_case;

	case IS_OBJECT:
	case IS_STRING: {
		zend_long lval;
		double dval;

		if (!try_convert_to_string(&lzval)) {
			ctx->err.has_error = 1;
			break;
		}

		switch (is_numeric_string(Z_STRVAL(lzval), Z_STRLEN(lzval), &lval, &dval, 0)) {
		case IS_DOUBLE:
			zval_ptr_dtor_str(&lzval);
			ZVAL_DOUBLE(&lzval, dval);
			goto double_case;

		case IS_LONG:
			zval_ptr_dtor_str(&lzval);
			ZVAL_LONG(&lzval, lval);
			goto long_case;
		}

		/* if we get here, we don't have a numeric string */
		do_from_zval_err(ctx, "expected an integer, but got a non numeric "
				"string (possibly from a converted object): '%s'", Z_STRVAL_P(arr_value));
		break;
	}

	default:
		do_from_zval_err(ctx, "%s", "expected an integer, either of a PHP "
				"integer type or of a convertible type");
		break;
	}

	zval_ptr_dtor(&lzval);

	return ret;
}