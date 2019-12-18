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
struct TYPE_4__ {scalar_t__ last_err; int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 scalar_t__ OCITransCommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ oci_drv_error (char*) ; 

__attribute__((used)) static int oci_handle_commit(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;

	H->last_err = OCITransCommit(H->svc, H->err, 0);

	if (H->last_err) {
		H->last_err = oci_drv_error("OCITransCommit");
		return 0;
	}
	return 1;
}