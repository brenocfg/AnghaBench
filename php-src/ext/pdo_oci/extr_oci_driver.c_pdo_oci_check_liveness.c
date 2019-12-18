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
typedef  int /*<<< orphan*/  version ;
typedef  int /*<<< orphan*/  ub4 ;
typedef  int /*<<< orphan*/  text ;
typedef  int sb4 ;
struct TYPE_4__ {scalar_t__ attached; scalar_t__ last_err; int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  OCIErrorGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OCIPing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OCIServerVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_HTYPE_ERROR ; 
 int /*<<< orphan*/  OCI_HTYPE_SVCCTX ; 
 scalar_t__ OCI_SUCCESS ; 
 int SUCCESS ; 

__attribute__((used)) static int pdo_oci_check_liveness(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;
	sb4 error_code = 0;
#if (!((OCI_MAJOR_VERSION > 10) || ((OCI_MAJOR_VERSION == 10) && (OCI_MINOR_VERSION >= 2))))
	char version[256];
#endif

	/* TODO move attached check to PDO level */
	if (H->attached == 0) {
		return FAILURE;
	}
	/* TODO add persistent_timeout check at PDO level */


	/* Use OCIPing instead of OCIServerVersion. If OCIPing returns ORA-1010 (invalid OCI operation)
	 * such as from Pre-10.1 servers, the error is still from the server and we would have
	 * successfully performed a roundtrip and validated the connection. Use OCIServerVersion for
	 * Pre-10.2 clients
	 */
#if ((OCI_MAJOR_VERSION > 10) || ((OCI_MAJOR_VERSION == 10) && (OCI_MINOR_VERSION >= 2)))	/* OCIPing available 10.2 onwards */
	H->last_err = OCIPing (H->svc, H->err, OCI_DEFAULT);
#else
	/* use good old OCIServerVersion() */
	H->last_err = OCIServerVersion (H->svc, H->err, (text *)version, sizeof(version), OCI_HTYPE_SVCCTX);
#endif
	if (H->last_err == OCI_SUCCESS) {
		return SUCCESS;
	}

	OCIErrorGet (H->err, (ub4)1, NULL, &error_code, NULL, 0, OCI_HTYPE_ERROR);

	if (error_code == 1010) {
		return SUCCESS;
	}
	return FAILURE;
}