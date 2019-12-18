#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  smart_str ;
struct TYPE_6__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ php_json_encoder ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_ARRAY 136 
#define  IS_DOUBLE 135 
#define  IS_FALSE 134 
#define  IS_LONG 133 
#define  IS_NULL 132 
#define  IS_OBJECT 131 
#define  IS_REFERENCE 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int /*<<< orphan*/  PHP_JSON_ERROR_INF_OR_NAN ; 
 int /*<<< orphan*/  PHP_JSON_ERROR_UNSUPPORTED_TYPE ; 
 int PHP_JSON_PARTIAL_OUTPUT_ON_ERROR ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_REFVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instanceof_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int php_json_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  php_json_encode_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int php_json_encode_serializable_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int php_json_escape_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  php_json_is_valid_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_json_serializable_ce ; 
 int /*<<< orphan*/  smart_str_append_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

int php_json_encode_zval(smart_str *buf, zval *val, int options, php_json_encoder *encoder) /* {{{ */
{
again:
	switch (Z_TYPE_P(val))
	{
		case IS_NULL:
			smart_str_appendl(buf, "null", 4);
			break;

		case IS_TRUE:
			smart_str_appendl(buf, "true", 4);
			break;
		case IS_FALSE:
			smart_str_appendl(buf, "false", 5);
			break;

		case IS_LONG:
			smart_str_append_long(buf, Z_LVAL_P(val));
			break;

		case IS_DOUBLE:
			if (php_json_is_valid_double(Z_DVAL_P(val))) {
				php_json_encode_double(buf, Z_DVAL_P(val), options);
			} else {
				encoder->error_code = PHP_JSON_ERROR_INF_OR_NAN;
				smart_str_appendc(buf, '0');
			}
			break;

		case IS_STRING:
			return php_json_escape_string(buf, Z_STRVAL_P(val), Z_STRLEN_P(val), options, encoder);

		case IS_OBJECT:
			if (instanceof_function(Z_OBJCE_P(val), php_json_serializable_ce)) {
				return php_json_encode_serializable_object(buf, val, options, encoder);
			}
			/* fallthrough -- Non-serializable object */
		case IS_ARRAY: {
			/* Avoid modifications (and potential freeing) of the array through a reference when a
			 * jsonSerialize() method is invoked. */
			zval zv;
			int res;
			ZVAL_COPY(&zv, val);
			res = php_json_encode_array(buf, &zv, options, encoder);
			zval_ptr_dtor_nogc(&zv);
			return res;
		}

		case IS_REFERENCE:
			val = Z_REFVAL_P(val);
			goto again;

		default:
			encoder->error_code = PHP_JSON_ERROR_UNSUPPORTED_TYPE;
			if (options & PHP_JSON_PARTIAL_OUTPUT_ON_ERROR) {
				smart_str_appendl(buf, "null", 4);
			}
			return FAILURE;
	}

	return SUCCESS;
}