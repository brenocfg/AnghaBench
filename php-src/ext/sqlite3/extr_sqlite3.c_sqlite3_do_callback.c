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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int size; int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * object; int /*<<< orphan*/  function_name; } ;
struct php_sqlite3_fci {int /*<<< orphan*/  fcc; TYPE_2__ fci; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int /*<<< orphan*/  zval_context; int /*<<< orphan*/  row_count; } ;
typedef  TYPE_1__ php_sqlite3_agg_context ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
#define  IS_DOUBLE 135 
#define  IS_LONG 134 
#define  IS_NULL 133 
#define  SQLITE3_TEXT 132 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  UNEXPECTED (int) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int zend_call_function (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_try_get_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sqlite3_do_callback(struct php_sqlite3_fci *fc, zval *cb, int argc, sqlite3_value **argv, sqlite3_context *context, int is_agg) /* {{{ */
{
	zval *zargs = NULL;
	zval retval;
	int i;
	int ret;
	int fake_argc;
	php_sqlite3_agg_context *agg_context = NULL;

	if (is_agg) {
		is_agg = 2;
	}

	fake_argc = argc + is_agg;

	fc->fci.size = sizeof(fc->fci);
	ZVAL_COPY_VALUE(&fc->fci.function_name, cb);
	fc->fci.object = NULL;
	fc->fci.retval = &retval;
	fc->fci.param_count = fake_argc;

	/* build up the params */

	if (fake_argc) {
		zargs = (zval *)safe_emalloc(fake_argc, sizeof(zval), 0);
	}

	if (is_agg) {
		/* summon the aggregation context */
		agg_context = (php_sqlite3_agg_context *)sqlite3_aggregate_context(context, sizeof(php_sqlite3_agg_context));

		if (Z_ISUNDEF(agg_context->zval_context)) {
			ZVAL_NULL(&agg_context->zval_context);
		}
		ZVAL_COPY(&zargs[0], &agg_context->zval_context);
		ZVAL_LONG(&zargs[1], agg_context->row_count);
	}

	for (i = 0; i < argc; i++) {
		switch (sqlite3_value_type(argv[i])) {
			case SQLITE_INTEGER:
#if ZEND_LONG_MAX > 2147483647
				ZVAL_LONG(&zargs[i + is_agg], sqlite3_value_int64(argv[i]));
#else
				ZVAL_LONG(&zargs[i + is_agg], sqlite3_value_int(argv[i]));
#endif
				break;

			case SQLITE_FLOAT:
				ZVAL_DOUBLE(&zargs[i + is_agg], sqlite3_value_double(argv[i]));
				break;

			case SQLITE_NULL:
				ZVAL_NULL(&zargs[i + is_agg]);
				break;

			case SQLITE_BLOB:
			case SQLITE3_TEXT:
			default:
				ZVAL_STRINGL(&zargs[i + is_agg], (char*)sqlite3_value_text(argv[i]), sqlite3_value_bytes(argv[i]));
				break;
		}
	}

	fc->fci.params = zargs;

	if ((ret = zend_call_function(&fc->fci, &fc->fcc)) == FAILURE) {
		php_error_docref(NULL, E_WARNING, "An error occurred while invoking the callback");
	}

	if (is_agg) {
		zval_ptr_dtor(&zargs[0]);
	}

	/* clean up the params */
	if (fake_argc) {
		for (i = is_agg; i < argc + is_agg; i++) {
			zval_ptr_dtor(&zargs[i]);
		}
		if (is_agg) {
			zval_ptr_dtor(&zargs[1]);
		}
		efree(zargs);
	}

	if (!is_agg || !argv) {
		/* only set the sqlite return value if we are a scalar function,
		 * or if we are finalizing an aggregate */
		if (!Z_ISUNDEF(retval)) {
			switch (Z_TYPE(retval)) {
				case IS_LONG:
#if ZEND_LONG_MAX > 2147483647
					sqlite3_result_int64(context, Z_LVAL(retval));
#else
					sqlite3_result_int(context, Z_LVAL(retval));
#endif
					break;

				case IS_NULL:
					sqlite3_result_null(context);
					break;

				case IS_DOUBLE:
					sqlite3_result_double(context, Z_DVAL(retval));
					break;

				default: {
					zend_string *str = zval_try_get_string(&retval);
					if (UNEXPECTED(!str)) {
						ret = FAILURE;
						break;
					}
					sqlite3_result_text(context, ZSTR_VAL(str), ZSTR_LEN(str), SQLITE_TRANSIENT);
					zend_string_release(str);
					break;
				}
			}
		} else {
			sqlite3_result_error(context, "failed to invoke callback", 0);
		}

		if (agg_context && !Z_ISUNDEF(agg_context->zval_context)) {
			zval_ptr_dtor(&agg_context->zval_context);
		}
	} else {
		/* we're stepping in an aggregate; the return value goes into
		 * the context */
		if (agg_context && !Z_ISUNDEF(agg_context->zval_context)) {
			zval_ptr_dtor(&agg_context->zval_context);
		}
		ZVAL_COPY_VALUE(&agg_context->zval_context, &retval);
		ZVAL_UNDEF(&retval);
	}

	if (!Z_ISUNDEF(retval)) {
		zval_ptr_dtor(&retval);
	}
	return ret;
}