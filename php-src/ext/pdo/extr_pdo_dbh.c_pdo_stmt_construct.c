#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_11__ {void* object; int /*<<< orphan*/  called_scope; scalar_t__ function_handler; } ;
typedef  TYPE_1__ zend_fcall_info_cache ;
struct TYPE_12__ {int size; int no_separation; int /*<<< orphan*/ * params; scalar_t__ param_count; int /*<<< orphan*/ * retval; void* object; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_2__ zend_fcall_info ;
typedef  int /*<<< orphan*/  zend_execute_data ;
struct TYPE_13__ {scalar_t__ constructor; } ;
typedef  TYPE_3__ zend_class_entry ;
struct TYPE_14__ {int /*<<< orphan*/  query_stringlen; int /*<<< orphan*/  query_string; } ;
typedef  TYPE_4__ pdo_stmt_t ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 void* Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_call_function (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_fcall_info_args (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_fcall_info_args_clear (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zend_std_write_property (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdo_stmt_construct(zend_execute_data *execute_data, pdo_stmt_t *stmt, zval *object, zend_class_entry *dbstmt_ce, zval *ctor_args) /* {{{ */
{
	zval query_string;
	zend_string *key;

	ZVAL_STRINGL(&query_string, stmt->query_string, stmt->query_stringlen);
	key = zend_string_init("queryString", sizeof("queryString") - 1, 0);
	zend_std_write_property(Z_OBJ_P(object), key, &query_string, NULL);
	zval_ptr_dtor(&query_string);
	zend_string_release_ex(key, 0);

	if (dbstmt_ce->constructor) {
		zend_fcall_info fci;
		zend_fcall_info_cache fcc;
		zval retval;

		fci.size = sizeof(zend_fcall_info);
		ZVAL_UNDEF(&fci.function_name);
		fci.object = Z_OBJ_P(object);
		fci.retval = &retval;
		fci.param_count = 0;
		fci.params = NULL;
		fci.no_separation = 1;

		zend_fcall_info_args(&fci, ctor_args);

		fcc.function_handler = dbstmt_ce->constructor;
		fcc.called_scope = Z_OBJCE_P(object);
		fcc.object = Z_OBJ_P(object);

		if (zend_call_function(&fci, &fcc) != FAILURE) {
			zval_ptr_dtor(&retval);
		}

		zend_fcall_info_args_clear(&fci, 1);
	}
}