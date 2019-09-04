#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ zend_reference ;
struct TYPE_9__ {int size; int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * object; int /*<<< orphan*/  function_name; } ;
struct pdo_sqlite_fci {int /*<<< orphan*/  fcc; TYPE_3__ fci; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__* GC_TYPE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  GC_SET_REFCOUNT (TYPE_1__*,int) ; 
#define  IS_DOUBLE 135 
#define  IS_LONG 134 
#define  IS_NULL 133 
 TYPE_2__* IS_REFERENCE ; 
#define  SQLITE3_TEXT 132 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_REF (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_string_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_aggregate_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int zend_call_function (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_callback(struct pdo_sqlite_fci *fc, zval *cb,
		int argc, sqlite3_value **argv, sqlite3_context *context,
		int is_agg)
{
	zval *zargs = NULL;
	zval retval;
	int i;
	int ret;
	int fake_argc;
	zend_reference *agg_context = NULL;

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
		zargs = safe_emalloc(fake_argc, sizeof(zval), 0);
	}

	if (is_agg) {
		agg_context = (zend_reference*)sqlite3_aggregate_context(context, sizeof(zend_reference));
		if (!agg_context) {
			ZVAL_NULL(&zargs[0]);
		} else {
			if (Z_ISUNDEF(agg_context->val)) {
				GC_SET_REFCOUNT(agg_context, 1);
				GC_TYPE_INFO(agg_context) = IS_REFERENCE;
				ZVAL_NULL(&agg_context->val);
			}
			ZVAL_REF(&zargs[0], agg_context);
		}
		ZVAL_LONG(&zargs[1], sqlite3_aggregate_count(context));
	}

	for (i = 0; i < argc; i++) {
		/* get the value */
		switch (sqlite3_value_type(argv[i])) {
			case SQLITE_INTEGER:
				ZVAL_LONG(&zargs[i + is_agg], sqlite3_value_int(argv[i]));
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

	/* clean up the params */
	if (zargs) {
		for (i = is_agg; i < fake_argc; i++) {
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
					sqlite3_result_int(context, Z_LVAL(retval));
					break;

				case IS_NULL:
					sqlite3_result_null(context);
					break;

				case IS_DOUBLE:
					sqlite3_result_double(context, Z_DVAL(retval));
					break;

				default:
					convert_to_string_ex(&retval);
					sqlite3_result_text(context, Z_STRVAL(retval), Z_STRLEN(retval), SQLITE_TRANSIENT);
					break;
			}
		} else {
			sqlite3_result_error(context, "failed to invoke callback", 0);
		}

		if (agg_context) {
			zval_ptr_dtor(&agg_context->val);
		}
	} else {
		/* we're stepping in an aggregate; the return value goes into
		 * the context */
		if (agg_context) {
			zval_ptr_dtor(&agg_context->val);
		}
		if (!Z_ISUNDEF(retval)) {
			ZVAL_COPY_VALUE(&agg_context->val, &retval);
			ZVAL_UNDEF(&retval);
		} else {
			ZVAL_UNDEF(&agg_context->val);
		}
	}

	if (!Z_ISUNDEF(retval)) {
		zval_ptr_dtor(&retval);
	}

	return ret;
}