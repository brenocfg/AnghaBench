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
typedef  scalar_t__ zend_long ;
typedef  int /*<<< orphan*/  ub4 ;
typedef  int /*<<< orphan*/  sb4 ;
struct TYPE_4__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {scalar_t__ last_err; int /*<<< orphan*/  err; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_oci_stmt ;
typedef  enum pdo_fetch_orientation { ____Placeholder_pdo_fetch_orientation } pdo_fetch_orientation ;

/* Variables and functions */
 scalar_t__ OCIStmtFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OCIStmtFetch2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_FETCH_ABSOLUTE ; 
 int /*<<< orphan*/  OCI_FETCH_FIRST ; 
 int /*<<< orphan*/  OCI_FETCH_LAST ; 
 int /*<<< orphan*/  OCI_FETCH_NEXT ; 
 int /*<<< orphan*/  OCI_FETCH_PRIOR ; 
 int /*<<< orphan*/  OCI_FETCH_RELATIVE ; 
 scalar_t__ OCI_NEED_DATA ; 
 scalar_t__ OCI_NO_DATA ; 
 scalar_t__ OCI_SUCCESS ; 
 scalar_t__ OCI_SUCCESS_WITH_INFO ; 
#define  PDO_FETCH_ORI_ABS 133 
#define  PDO_FETCH_ORI_FIRST 132 
#define  PDO_FETCH_ORI_LAST 131 
#define  PDO_FETCH_ORI_NEXT 130 
#define  PDO_FETCH_ORI_PRIOR 129 
#define  PDO_FETCH_ORI_REL 128 
 int /*<<< orphan*/  oci_stmt_error (char*) ; 

__attribute__((used)) static int oci_stmt_fetch(pdo_stmt_t *stmt, enum pdo_fetch_orientation ori,	zend_long offset) /* {{{ */
{
#if HAVE_OCISTMTFETCH2
	ub4 ociori;
#endif
	pdo_oci_stmt *S = (pdo_oci_stmt*)stmt->driver_data;

#if HAVE_OCISTMTFETCH2
	switch (ori) {
		case PDO_FETCH_ORI_NEXT:	ociori = OCI_FETCH_NEXT; break;
		case PDO_FETCH_ORI_PRIOR:	ociori = OCI_FETCH_PRIOR; break;
		case PDO_FETCH_ORI_FIRST:	ociori = OCI_FETCH_FIRST; break;
		case PDO_FETCH_ORI_LAST:	ociori = OCI_FETCH_LAST; break;
		case PDO_FETCH_ORI_ABS:		ociori = OCI_FETCH_ABSOLUTE; break;
		case PDO_FETCH_ORI_REL:		ociori = OCI_FETCH_RELATIVE; break;
	}
	S->last_err = OCIStmtFetch2(S->stmt, S->err, 1, ociori, (sb4) offset, OCI_DEFAULT);
#else
	S->last_err = OCIStmtFetch(S->stmt, S->err, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
#endif

	if (S->last_err == OCI_NO_DATA) {
		/* no (more) data */
		return 0;
	}

	if (S->last_err == OCI_NEED_DATA) {
		oci_stmt_error("OCI_NEED_DATA");
		return 0;
	}

	if (S->last_err == OCI_SUCCESS_WITH_INFO || S->last_err == OCI_SUCCESS) {
		return 1;
	}

	oci_stmt_error("OCIStmtFetch");

	return 0;
}