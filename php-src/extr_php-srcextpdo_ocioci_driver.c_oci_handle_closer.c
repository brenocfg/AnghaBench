#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* errmsg; } ;
struct TYPE_7__ {TYPE_1__ einfo; int /*<<< orphan*/ * env; scalar_t__ charset; int /*<<< orphan*/ * err; int /*<<< orphan*/ * server; scalar_t__ attached; scalar_t__ last_err; int /*<<< orphan*/ * svc; int /*<<< orphan*/ * session; } ;
typedef  TYPE_2__ pdo_oci_db_handle ;
struct TYPE_8__ {int /*<<< orphan*/  is_persistent; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCIHandleFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OCIServerDetach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCITransRollback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_HTYPE_ENV ; 
 int /*<<< orphan*/  OCI_HTYPE_ERROR ; 
 int /*<<< orphan*/  OCI_HTYPE_SERVER ; 
 int /*<<< orphan*/  OCI_HTYPE_SESSION ; 
 int /*<<< orphan*/  OCI_HTYPE_SVCCTX ; 
 int /*<<< orphan*/  oci_drv_error (char*) ; 
 int /*<<< orphan*/  pefree (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oci_handle_closer(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;

	if (H->svc) {
		/* rollback any outstanding work */
		OCITransRollback(H->svc, H->err, 0);
	}

	if (H->session) {
		OCIHandleFree(H->session, OCI_HTYPE_SESSION);
		H->session = NULL;
	}

	if (H->svc) {
		OCIHandleFree(H->svc, OCI_HTYPE_SVCCTX);
		H->svc = NULL;
	}

	if (H->server && H->attached) {
		H->last_err = OCIServerDetach(H->server, H->err, OCI_DEFAULT);
		if (H->last_err) {
			oci_drv_error("OCIServerDetach");
		}
		H->attached = 0;
	}

	if (H->server) {
		OCIHandleFree(H->server, OCI_HTYPE_SERVER);
		H->server = NULL;
	}

	if (H->err) {
		OCIHandleFree(H->err, OCI_HTYPE_ERROR);
		H->err = NULL;
	}

	if (H->charset && H->env) {
		OCIHandleFree(H->env, OCI_HTYPE_ENV);
		H->env = NULL;
	}

	if (H->einfo.errmsg) {
		pefree(H->einfo.errmsg, dbh->is_persistent);
		H->einfo.errmsg = NULL;
	}

	pefree(H, dbh->is_persistent);

	return 0;
}