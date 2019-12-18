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
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_5__ {char* error_code; } ;
typedef  TYPE_1__ pdo_stmt_t ;
typedef  char* pdo_error_type ;
struct TYPE_6__ {char* error_code; scalar_t__ error_mode; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ PDO_ERRMODE_EXCEPTION ; 
 scalar_t__ PDO_ERRMODE_SILENT ; 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdo_sqlstate_state_to_description (char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * php_pdo_get_exception () ; 
 int /*<<< orphan*/ * php_pdo_get_exception_base (int) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  zend_throw_exception_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_update_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_update_property_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void pdo_raise_impl_error(pdo_dbh_t *dbh, pdo_stmt_t *stmt, const char *sqlstate, const char *supp) /* {{{ */
{
	pdo_error_type *pdo_err = &dbh->error_code;
	char *message = NULL;
	const char *msg;

	if (dbh && dbh->error_mode == PDO_ERRMODE_SILENT) {
#if 0
		/* BUG: if user is running in silent mode and hits an error at the driver level
		 * when they use the PDO methods to call up the error information, they may
		 * get bogus information */
		return;
#endif
	}

	if (stmt) {
		pdo_err = &stmt->error_code;
	}

	strncpy(*pdo_err, sqlstate, 6);

	/* hash sqlstate to error messages */
	msg = pdo_sqlstate_state_to_description(*pdo_err);
	if (!msg) {
		msg = "<<Unknown error>>";
	}

	if (supp) {
		spprintf(&message, 0, "SQLSTATE[%s]: %s: %s", *pdo_err, msg, supp);
	} else {
		spprintf(&message, 0, "SQLSTATE[%s]: %s", *pdo_err, msg);
	}

	if (dbh && dbh->error_mode != PDO_ERRMODE_EXCEPTION) {
		php_error_docref(NULL, E_WARNING, "%s", message);
	} else {
		zval ex, info;
		zend_class_entry *def_ex = php_pdo_get_exception_base(1), *pdo_ex = php_pdo_get_exception();

		object_init_ex(&ex, pdo_ex);

		zend_update_property_string(def_ex, &ex, "message", sizeof("message")-1, message);
		zend_update_property_string(def_ex, &ex, "code", sizeof("code")-1, *pdo_err);

		array_init(&info);

		add_next_index_string(&info, *pdo_err);
		add_next_index_long(&info, 0);
		zend_update_property(pdo_ex, &ex, "errorInfo", sizeof("errorInfo")-1, &info);
		zval_ptr_dtor(&info);

		zend_throw_exception_object(&ex);
	}

	if (message) {
		efree(message);
	}
}