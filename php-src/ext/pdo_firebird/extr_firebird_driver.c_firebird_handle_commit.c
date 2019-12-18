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
struct TYPE_5__ {int /*<<< orphan*/  tr; int /*<<< orphan*/  isc_status; } ;
typedef  TYPE_1__ pdo_firebird_db_handle ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_ERROR (TYPE_2__*) ; 
 scalar_t__ isc_commit_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int firebird_handle_commit(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_firebird_db_handle *H = (pdo_firebird_db_handle *)dbh->driver_data;

	if (isc_commit_transaction(H->isc_status, &H->tr)) {
		RECORD_ERROR(dbh);
		return 0;
	}
	return 1;
}