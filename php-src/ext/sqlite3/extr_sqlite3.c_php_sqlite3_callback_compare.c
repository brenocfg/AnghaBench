#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int size; int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * object; int /*<<< orphan*/  function_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcc; TYPE_3__ fci; } ;
struct TYPE_5__ {TYPE_1__ fci; int /*<<< orphan*/  cmp_func; } ;
typedef  TYPE_2__ php_sqlite3_collation ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,void const*,int) ; 
 int Z_LVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int zend_call_function (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_sqlite3_callback_compare(void *coll, int a_len, const void *a, int b_len, const void* b) /* {{{ */
{
	php_sqlite3_collation *collation = (php_sqlite3_collation*)coll;
	zval zargs[2];
	zval retval;
	int ret;

	// Exception occurred on previous callback. Don't attempt to call function.
	if (EG(exception)) {
		return 0;
	}

	collation->fci.fci.size = (sizeof(collation->fci.fci));
	ZVAL_COPY_VALUE(&collation->fci.fci.function_name, &collation->cmp_func);
	collation->fci.fci.object = NULL;
	collation->fci.fci.retval = &retval;
	collation->fci.fci.param_count = 2;

	ZVAL_STRINGL(&zargs[0], a, a_len);
	ZVAL_STRINGL(&zargs[1], b, b_len);

	collation->fci.fci.params = zargs;

	if ((ret = zend_call_function(&collation->fci.fci, &collation->fci.fcc)) == FAILURE) {
		php_error_docref(NULL, E_WARNING, "An error occurred while invoking the compare callback");
	}

	zval_ptr_dtor(&zargs[0]);
	zval_ptr_dtor(&zargs[1]);

	if (EG(exception)) {
		ret = 0;
	} else if (Z_TYPE(retval) != IS_LONG){
		//retval ought to contain a ZVAL_LONG by now
		// (the result of a comparison, i.e. most likely -1, 0, or 1)
		//I suppose we could accept any scalar return type, though.
		php_error_docref(NULL, E_WARNING, "An error occurred while invoking the compare callback (invalid return type).  Collation behaviour is undefined.");
	} else {
		ret = Z_LVAL(retval);
	}

	zval_ptr_dtor(&retval);

	return ret;
}