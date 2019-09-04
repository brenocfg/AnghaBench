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
struct TYPE_5__ {int /*<<< orphan*/ * login; int /*<<< orphan*/ * link; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_6__ {int /*<<< orphan*/ * driver_data; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbfreelogin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_dblib_err_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dblib_handle_closer(pdo_dbh_t *dbh)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;

	if (H) {
		pdo_dblib_err_dtor(&H->err);
		if (H->link) {
			dbclose(H->link);
			H->link = NULL;
		}
		if (H->login) {
			dbfreelogin(H->login);
			H->login = NULL;
		}
		pefree(H, dbh->is_persistent);
		dbh->driver_data = NULL;
	}
	return 0;
}