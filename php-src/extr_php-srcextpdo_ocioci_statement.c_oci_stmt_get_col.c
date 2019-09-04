#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  database_object_handle; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_9__ {int /*<<< orphan*/  err; TYPE_1__* H; TYPE_4__* cols; } ;
typedef  TYPE_3__ pdo_oci_stmt ;
struct TYPE_10__ {int indicator; scalar_t__ dtype; char* data; scalar_t__ fetched_len; } ;
typedef  TYPE_4__ pdo_oci_column ;
struct TYPE_7__ {int /*<<< orphan*/  svc; } ;
typedef  int /*<<< orphan*/  OCILobLocator ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  OCILobOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_LOB_READONLY ; 
 scalar_t__ SQLT_BLOB ; 
 scalar_t__ SQLT_CLOB ; 
 scalar_t__ oci_create_lob_stream (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int oci_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, size_t *len, int *caller_frees) /* {{{ */
{
	pdo_oci_stmt *S = (pdo_oci_stmt*)stmt->driver_data;
	pdo_oci_column *C = &S->cols[colno];

	/* check the indicator to ensure that the data is intact */
	if (C->indicator == -1) {
		/* A NULL value */
		*ptr = NULL;
		*len = 0;
		return 1;
	} else if (C->indicator == 0) {
		/* it was stored perfectly */

		if (C->dtype == SQLT_BLOB || C->dtype == SQLT_CLOB) {
			if (C->data) {
				*ptr = (char*)oci_create_lob_stream(&stmt->database_object_handle, stmt, (OCILobLocator*)C->data);
				OCILobOpen(S->H->svc, S->err, (OCILobLocator*)C->data, OCI_LOB_READONLY);
			}
			*len = (size_t) 0;
			return *ptr ? 1 : 0;
		}

		*ptr = C->data;
		*len = (size_t) C->fetched_len;
		return 1;
	} else {
		/* it was truncated */
		php_error_docref(NULL, E_WARNING, "column %d data was too large for buffer and was truncated to fit it", colno);

		*ptr = C->data;
		*len = (size_t) C->fetched_len;
		return 1;
	}
}