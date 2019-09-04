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
struct TYPE_4__ {int size; int param_count; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * object; int /*<<< orphan*/  function_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  fcc; TYPE_2__ fci; } ;
struct pdo_sqlite_collation {TYPE_1__ fc; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_LVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_long_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int zend_call_function (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_sqlite3_collation_callback(void *context,
	int string1_len, const void *string1,
	int string2_len, const void *string2)
{
	int ret;
	zval zargs[2];
	zval retval;
	struct pdo_sqlite_collation *collation = (struct pdo_sqlite_collation*) context;

	collation->fc.fci.size = sizeof(collation->fc.fci);
	ZVAL_COPY_VALUE(&collation->fc.fci.function_name, &collation->callback);
	collation->fc.fci.object = NULL;
	collation->fc.fci.retval = &retval;

	// Prepare the arguments.
	ZVAL_STRINGL(&zargs[0], (char *) string1, string1_len);
	ZVAL_STRINGL(&zargs[1], (char *) string2, string2_len);
	collation->fc.fci.param_count = 2;
	collation->fc.fci.params = zargs;

	if ((ret = zend_call_function(&collation->fc.fci, &collation->fc.fcc)) == FAILURE) {
		php_error_docref(NULL, E_WARNING, "An error occurred while invoking the callback");
	} else if (!Z_ISUNDEF(retval)) {
		if (Z_TYPE(retval) != IS_LONG) {
			convert_to_long_ex(&retval);
		}
		ret = 0;
		if (Z_LVAL(retval) > 0) {
			ret = 1;
		} else if (Z_LVAL(retval) < 0) {
			ret = -1;
		}
		zval_ptr_dtor(&retval);
	}

	zval_ptr_dtor(&zargs[0]);
	zval_ptr_dtor(&zargs[1]);

	return ret;
}