#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct pdo_bound_param_data {int paramno; int /*<<< orphan*/  parameter; int /*<<< orphan*/  param_type; int /*<<< orphan*/  name; int /*<<< orphan*/  is_param; } ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_6__ {int /*<<< orphan*/  dbh; int /*<<< orphan*/  executed; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {int done; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_sqlite_stmt ;
typedef  enum pdo_param_event { ____Placeholder_pdo_param_event } pdo_param_event ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  IS_RESOURCE ; 
#define  PDO_PARAM_BOOL 134 
#define  PDO_PARAM_EVT_EXEC_PRE 133 
#define  PDO_PARAM_INT 132 
#define  PDO_PARAM_LOB 131 
#define  PDO_PARAM_NULL 130 
#define  PDO_PARAM_STMT 129 
#define  PDO_PARAM_STR 128 
 int /*<<< orphan*/  PDO_PARAM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_STREAM_COPY_ALL ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/ * ZSTR_EMPTY_ALLOC () ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_raise_impl_error (int /*<<< orphan*/ ,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  pdo_sqlite_error_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/ * php_stream_copy_to_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_from_zval_no_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_parameter_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_sqlite_stmt_param_hook(pdo_stmt_t *stmt, struct pdo_bound_param_data *param,
		enum pdo_param_event event_type)
{
	pdo_sqlite_stmt *S = (pdo_sqlite_stmt*)stmt->driver_data;
	zval *parameter;

	switch (event_type) {
		case PDO_PARAM_EVT_EXEC_PRE:
			if (stmt->executed && !S->done) {
				sqlite3_reset(S->stmt);
				S->done = 1;
			}

			if (param->is_param) {

				if (param->paramno == -1) {
					param->paramno = sqlite3_bind_parameter_index(S->stmt, ZSTR_VAL(param->name)) - 1;
				}

				switch (PDO_PARAM_TYPE(param->param_type)) {
					case PDO_PARAM_STMT:
						return 0;

					case PDO_PARAM_NULL:
						if (sqlite3_bind_null(S->stmt, param->paramno + 1) == SQLITE_OK) {
							return 1;
						}
						pdo_sqlite_error_stmt(stmt);
						return 0;

					case PDO_PARAM_INT:
					case PDO_PARAM_BOOL:
						if (Z_ISREF(param->parameter)) {
							parameter = Z_REFVAL(param->parameter);
						} else {
							parameter = &param->parameter;
						}
						if (Z_TYPE_P(parameter) == IS_NULL) {
							if (sqlite3_bind_null(S->stmt, param->paramno + 1) == SQLITE_OK) {
								return 1;
							}
						} else {
							convert_to_long(parameter);
#if ZEND_LONG_MAX > 2147483647
							if (SQLITE_OK == sqlite3_bind_int64(S->stmt, param->paramno + 1, Z_LVAL_P(parameter))) {
								return 1;
							}
#else
							if (SQLITE_OK == sqlite3_bind_int(S->stmt, param->paramno + 1, Z_LVAL_P(parameter))) {
								return 1;
							}
#endif
						}
						pdo_sqlite_error_stmt(stmt);
						return 0;

					case PDO_PARAM_LOB:
						if (Z_ISREF(param->parameter)) {
							parameter = Z_REFVAL(param->parameter);
						} else {
							parameter = &param->parameter;
						}
						if (Z_TYPE_P(parameter) == IS_RESOURCE) {
							php_stream *stm = NULL;
							php_stream_from_zval_no_verify(stm, parameter);
							if (stm) {
								zend_string *mem = php_stream_copy_to_mem(stm, PHP_STREAM_COPY_ALL, 0);
								zval_ptr_dtor(parameter);
								ZVAL_STR(parameter, mem ? mem : ZSTR_EMPTY_ALLOC());
							} else {
								pdo_raise_impl_error(stmt->dbh, stmt, "HY105", "Expected a stream resource");
								return 0;
							}
						} else if (Z_TYPE_P(parameter) == IS_NULL) {
							if (sqlite3_bind_null(S->stmt, param->paramno + 1) == SQLITE_OK) {
								return 1;
							}
							pdo_sqlite_error_stmt(stmt);
							return 0;
						} else {
							if (!try_convert_to_string(parameter)) {
								return 0;
							}
						}

						if (SQLITE_OK == sqlite3_bind_blob(S->stmt, param->paramno + 1,
								Z_STRVAL_P(parameter),
								Z_STRLEN_P(parameter),
								SQLITE_STATIC)) {
							return 1;
						}
						return 0;

					case PDO_PARAM_STR:
					default:
						if (Z_ISREF(param->parameter)) {
							parameter = Z_REFVAL(param->parameter);
						} else {
							parameter = &param->parameter;
						}
						if (Z_TYPE_P(parameter) == IS_NULL) {
							if (sqlite3_bind_null(S->stmt, param->paramno + 1) == SQLITE_OK) {
								return 1;
							}
						} else {
							if (!try_convert_to_string(parameter)) {
								return 0;
							}
							if (SQLITE_OK == sqlite3_bind_text(S->stmt, param->paramno + 1,
									Z_STRVAL_P(parameter),
									Z_STRLEN_P(parameter),
									SQLITE_STATIC)) {
								return 1;
							}
						}
						pdo_sqlite_error_stmt(stmt);
						return 0;
				}
			}
			break;

		default:
			;
	}
	return 1;
}