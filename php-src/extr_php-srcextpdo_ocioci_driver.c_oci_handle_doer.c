#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_long ;
typedef  scalar_t__ ub4 ;
typedef  scalar_t__ ub2 ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_4__ {int /*<<< orphan*/  err; void* last_err; int /*<<< orphan*/  svc; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_5__ {int /*<<< orphan*/  in_txn; scalar_t__ auto_commit; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  dvoid ;
typedef  int /*<<< orphan*/  OCIStmt ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 void* OCIAttrGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCIHandleAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCIHandleFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* OCIStmtExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* OCIStmtPrepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_ATTR_ROW_COUNT ; 
 int /*<<< orphan*/  OCI_ATTR_STMT_TYPE ; 
 int /*<<< orphan*/  OCI_COMMIT_ON_SUCCESS ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_HTYPE_STMT ; 
 int /*<<< orphan*/  OCI_NTV_SYNTAX ; 
 scalar_t__ OCI_STMT_SELECT ; 
 void* oci_drv_error (char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static zend_long oci_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len) /* {{{ */
{
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;
	OCIStmt		*stmt;
	ub2 stmt_type;
	ub4 rowcount;
	int ret = -1;

	OCIHandleAlloc(H->env, (dvoid*)&stmt, OCI_HTYPE_STMT, 0, NULL);

	H->last_err = OCIStmtPrepare(stmt, H->err, (text*)sql, (ub4) sql_len, OCI_NTV_SYNTAX, OCI_DEFAULT);
	if (H->last_err) {
		H->last_err = oci_drv_error("OCIStmtPrepare");
		OCIHandleFree(stmt, OCI_HTYPE_STMT);
		return -1;
	}

	H->last_err = OCIAttrGet(stmt, OCI_HTYPE_STMT, &stmt_type, 0, OCI_ATTR_STMT_TYPE, H->err);

	if (stmt_type == OCI_STMT_SELECT) {
		/* invalid usage; cancel it */
		OCIHandleFree(stmt, OCI_HTYPE_STMT);
		php_error_docref(NULL, E_WARNING, "issuing a SELECT query here is invalid");
		return -1;
	}

	/* now we are good to go */
	H->last_err = OCIStmtExecute(H->svc, stmt, H->err, 1, 0, NULL, NULL,
			(dbh->auto_commit && !dbh->in_txn) ? OCI_COMMIT_ON_SUCCESS : OCI_DEFAULT);

	if (H->last_err) {
		H->last_err = oci_drv_error("OCIStmtExecute");
	} else {
		/* return the number of affected rows */
		H->last_err = OCIAttrGet(stmt, OCI_HTYPE_STMT, &rowcount, 0, OCI_ATTR_ROW_COUNT, H->err);
		ret = rowcount;
	}

	OCIHandleFree(stmt, OCI_HTYPE_STMT);

	return ret;
}