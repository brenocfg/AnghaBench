#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ub4 ;
struct TYPE_10__ {int column_count; long row_count; scalar_t__ executed; TYPE_1__* dbh; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_11__ {scalar_t__ stmt_type; scalar_t__ exec_type; int /*<<< orphan*/  err; int /*<<< orphan*/  stmt; TYPE_6__* cols; int /*<<< orphan*/  have_blobs; TYPE_2__* H; } ;
typedef  TYPE_4__ pdo_oci_stmt ;
typedef  int /*<<< orphan*/  pdo_oci_column ;
typedef  scalar_t__ b4 ;
struct TYPE_12__ {int dtype; struct TYPE_12__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  svc; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_txn; scalar_t__ auto_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCIAttrGet ; 
 int /*<<< orphan*/  OCIStmtExecute ; 
 int /*<<< orphan*/  OCIStmtFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OCI_ATTR_PARAM_COUNT ; 
 int /*<<< orphan*/  OCI_ATTR_ROW_COUNT ; 
 int /*<<< orphan*/  OCI_ATTR_STMT_TYPE ; 
 scalar_t__ OCI_COMMIT_ON_SUCCESS ; 
 scalar_t__ OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_FETCH_NEXT ; 
 int /*<<< orphan*/  OCI_HTYPE_STMT ; 
 scalar_t__ OCI_STMT_SCROLLABLE_READONLY ; 
 scalar_t__ OCI_STMT_SELECT ; 
#define  SQLT_BLOB 129 
#define  SQLT_CLOB 128 
 int /*<<< orphan*/  STMT_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMT_CALL_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ecalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  efree (TYPE_6__*) ; 

__attribute__((used)) static int oci_stmt_execute(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_oci_stmt *S = (pdo_oci_stmt*)stmt->driver_data;
	ub4 rowcount;
	b4 mode;

	if (!S->stmt_type) {
		STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_STMT_TYPE",
				(S->stmt, OCI_HTYPE_STMT, &S->stmt_type, 0, OCI_ATTR_STMT_TYPE, S->err));
	}

	if (stmt->executed) {
		/* ensure that we cancel the cursor from a previous fetch */
		OCIStmtFetch(S->stmt, S->err, 0, OCI_FETCH_NEXT, OCI_DEFAULT);
	}

#ifdef OCI_STMT_SCROLLABLE_READONLY /* needed for oci8 ? */
	if (S->exec_type == OCI_STMT_SCROLLABLE_READONLY) {
		mode = OCI_STMT_SCROLLABLE_READONLY;
	} else
#endif
	if (stmt->dbh->auto_commit && !stmt->dbh->in_txn) {
		mode = OCI_COMMIT_ON_SUCCESS;
	} else {
		mode = OCI_DEFAULT;
	}

	STMT_CALL(OCIStmtExecute, (S->H->svc, S->stmt, S->err,
				(S->stmt_type == OCI_STMT_SELECT && !S->have_blobs) ? 0 : 1, 0, NULL, NULL,
				mode));

	if (!stmt->executed) {
		ub4 colcount;
		/* do first-time-only definition of bind/mapping stuff */

		/* how many columns do we have ? */
		STMT_CALL_MSG(OCIAttrGet, "ATTR_PARAM_COUNT",
				(S->stmt, OCI_HTYPE_STMT, &colcount, 0, OCI_ATTR_PARAM_COUNT, S->err));

		stmt->column_count = (int)colcount;

		if (S->cols) {
			int i;
			for (i = 0; i < stmt->column_count; i++) {
				if (S->cols[i].data) {
					switch (S->cols[i].dtype) {
						case SQLT_BLOB:
						case SQLT_CLOB:
							/* do nothing */
							break;
						default:
							efree(S->cols[i].data);
					}
				}
			}
			efree(S->cols);
		}

		S->cols = ecalloc(colcount, sizeof(pdo_oci_column));
	}

	STMT_CALL_MSG(OCIAttrGet, "ATTR_ROW_COUNT",
			(S->stmt, OCI_HTYPE_STMT, &rowcount, 0, OCI_ATTR_ROW_COUNT, S->err));
	stmt->row_count = (long)rowcount;

	return 1;
}