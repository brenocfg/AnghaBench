#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_14__ {TYPE_2__* constructor; } ;
typedef  TYPE_4__ zend_class_entry ;
struct TYPE_15__ {int error_mode; int desired_case; int default_fetch_type; int stringify; TYPE_3__* methods; int /*<<< orphan*/  def_stmt_ctor_args; TYPE_4__* def_stmt_ce; int /*<<< orphan*/  is_persistent; void* oracle_nulls; } ;
typedef  TYPE_5__ pdo_dbh_t ;
struct TYPE_13__ {scalar_t__ (* set_attribute ) (TYPE_5__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int fn_flags; } ;
struct TYPE_12__ {TYPE_1__ common; } ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  IS_ARRAY ; 
 int /*<<< orphan*/  IS_FALSE ; 
 int /*<<< orphan*/  IS_LONG ; 
 int /*<<< orphan*/  IS_STRING ; 
 int /*<<< orphan*/  IS_TRUE ; 
 int PDO_ATTR_AUTOCOMMIT ; 
#define  PDO_ATTR_CASE 139 
#define  PDO_ATTR_DEFAULT_FETCH_MODE 138 
#define  PDO_ATTR_ERRMODE 137 
#define  PDO_ATTR_ORACLE_NULLS 136 
#define  PDO_ATTR_STATEMENT_CLASS 135 
#define  PDO_ATTR_STRINGIFY_FETCHES 134 
#define  PDO_CASE_LOWER 133 
#define  PDO_CASE_NATURAL 132 
#define  PDO_CASE_UPPER 131 
 int /*<<< orphan*/  PDO_DBH_CLEAR_ERR () ; 
#define  PDO_ERRMODE_EXCEPTION 130 
#define  PDO_ERRMODE_SILENT 129 
#define  PDO_ERRMODE_WARNING 128 
 int /*<<< orphan*/  PDO_FETCH_CLASS ; 
 int /*<<< orphan*/  PDO_FETCH_INTO ; 
 int PDO_FETCH_USE_DEFAULT ; 
 int /*<<< orphan*/  PDO_HANDLE_DBH_ERR () ; 
 int SUCCESS ; 
 int ZEND_ACC_PRIVATE ; 
 int ZEND_ACC_PROTECTED ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instanceof_function (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_dbstmt_ce ; 
 int /*<<< orphan*/  pdo_raise_impl_error (TYPE_5__*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 scalar_t__ stub1 (TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* zend_lookup_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* zval_get_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_dbh_attribute_set(pdo_dbh_t *dbh, zend_long attr, zval *value) /* {{{ */
{
	zend_long lval;

#define PDO_LONG_PARAM_CHECK \
	if (Z_TYPE_P(value) != IS_LONG && Z_TYPE_P(value) != IS_STRING && Z_TYPE_P(value) != IS_FALSE && Z_TYPE_P(value) != IS_TRUE) { \
		pdo_raise_impl_error(dbh, NULL, "HY000", "attribute value must be an integer"); \
		PDO_HANDLE_DBH_ERR(); \
		return FAILURE; \
	} \

	switch (attr) {
		case PDO_ATTR_ERRMODE:
			PDO_LONG_PARAM_CHECK;
			lval = zval_get_long(value);
			switch (lval) {
				case PDO_ERRMODE_SILENT:
				case PDO_ERRMODE_WARNING:
				case PDO_ERRMODE_EXCEPTION:
					dbh->error_mode = lval;
					return SUCCESS;
				default:
					pdo_raise_impl_error(dbh, NULL, "HY000", "invalid error mode");
					PDO_HANDLE_DBH_ERR();
					return FAILURE;
			}
			return FAILURE;

		case PDO_ATTR_CASE:
			PDO_LONG_PARAM_CHECK;
			lval = zval_get_long(value);
			switch (lval) {
				case PDO_CASE_NATURAL:
				case PDO_CASE_UPPER:
				case PDO_CASE_LOWER:
					dbh->desired_case = lval;
					return SUCCESS;
				default:
					pdo_raise_impl_error(dbh, NULL, "HY000", "invalid case folding mode");
					PDO_HANDLE_DBH_ERR();
					return FAILURE;
			}
			return FAILURE;

		case PDO_ATTR_ORACLE_NULLS:
			PDO_LONG_PARAM_CHECK;
			dbh->oracle_nulls = zval_get_long(value);
			return SUCCESS;

		case PDO_ATTR_DEFAULT_FETCH_MODE:
			if (Z_TYPE_P(value) == IS_ARRAY) {
				zval *tmp;
				if ((tmp = zend_hash_index_find(Z_ARRVAL_P(value), 0)) != NULL && Z_TYPE_P(tmp) == IS_LONG) {
					if (Z_LVAL_P(tmp) == PDO_FETCH_INTO || Z_LVAL_P(tmp) == PDO_FETCH_CLASS) {
						pdo_raise_impl_error(dbh, NULL, "HY000", "FETCH_INTO and FETCH_CLASS are not yet supported as default fetch modes");
						return FAILURE;
					}
				}
			} else {
				PDO_LONG_PARAM_CHECK;
			}
			lval = zval_get_long(value);
			if (lval == PDO_FETCH_USE_DEFAULT) {
				pdo_raise_impl_error(dbh, NULL, "HY000", "invalid fetch mode type");
				return FAILURE;
			}
			dbh->default_fetch_type = lval;
			return SUCCESS;

		case PDO_ATTR_STRINGIFY_FETCHES:
			PDO_LONG_PARAM_CHECK;
			dbh->stringify = zval_get_long(value) ? 1 : 0;
			return SUCCESS;

		case PDO_ATTR_STATEMENT_CLASS: {
			/* array(string classname, array(mixed ctor_args)) */
			zend_class_entry *pce;
			zval *item;

			if (dbh->is_persistent) {
				pdo_raise_impl_error(dbh, NULL, "HY000",
					"PDO::ATTR_STATEMENT_CLASS cannot be used with persistent PDO instances"
					);
				PDO_HANDLE_DBH_ERR();
				return FAILURE;
			}
			if (Z_TYPE_P(value) != IS_ARRAY
				|| (item = zend_hash_index_find(Z_ARRVAL_P(value), 0)) == NULL
				|| Z_TYPE_P(item) != IS_STRING
				|| (pce = zend_lookup_class(Z_STR_P(item))) == NULL
			) {
				pdo_raise_impl_error(dbh, NULL, "HY000",
					"PDO::ATTR_STATEMENT_CLASS requires format array(classname, array(ctor_args)); "
					"the classname must be a string specifying an existing class"
					);
				PDO_HANDLE_DBH_ERR();
				return FAILURE;
			}
			if (!instanceof_function(pce, pdo_dbstmt_ce)) {
				pdo_raise_impl_error(dbh, NULL, "HY000",
					"user-supplied statement class must be derived from PDOStatement");
				PDO_HANDLE_DBH_ERR();
				return FAILURE;
			}
			if (pce->constructor && !(pce->constructor->common.fn_flags & (ZEND_ACC_PRIVATE|ZEND_ACC_PROTECTED))) {
				pdo_raise_impl_error(dbh, NULL, "HY000",
					"user-supplied statement class cannot have a public constructor");
				PDO_HANDLE_DBH_ERR();
				return FAILURE;
			}
			dbh->def_stmt_ce = pce;
			if (!Z_ISUNDEF(dbh->def_stmt_ctor_args)) {
				zval_ptr_dtor(&dbh->def_stmt_ctor_args);
				ZVAL_UNDEF(&dbh->def_stmt_ctor_args);
			}
			if ((item = zend_hash_index_find(Z_ARRVAL_P(value), 1)) != NULL) {
				if (Z_TYPE_P(item) != IS_ARRAY) {
					pdo_raise_impl_error(dbh, NULL, "HY000",
						"PDO::ATTR_STATEMENT_CLASS requires format array(classname, array(ctor_args)); "
						"ctor_args must be an array"
					);
					PDO_HANDLE_DBH_ERR();
					return FAILURE;
				}
				ZVAL_COPY(&dbh->def_stmt_ctor_args, item);
			}
			return SUCCESS;
		}

		default:
			;
	}

	if (!dbh->methods->set_attribute) {
		goto fail;
	}

	PDO_DBH_CLEAR_ERR();
	if (dbh->methods->set_attribute(dbh, attr, value)) {
		return SUCCESS;
	}

fail:
	if (attr == PDO_ATTR_AUTOCOMMIT) {
		zend_throw_exception_ex(php_pdo_get_exception(), 0, "The auto-commit mode cannot be changed for this driver");
	} else if (!dbh->methods->set_attribute) {
		pdo_raise_impl_error(dbh, NULL, "IM001", "driver does not support setting attributes");
	} else {
		PDO_HANDLE_DBH_ERR();
	}
	return FAILURE;
}