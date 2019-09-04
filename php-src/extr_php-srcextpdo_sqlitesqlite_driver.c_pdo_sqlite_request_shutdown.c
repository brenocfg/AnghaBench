#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdo_sqlite_db_handle ;
struct TYPE_3__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdo_sqlite_cleanup_callbacks (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdo_sqlite_request_shutdown(pdo_dbh_t *dbh)
{
	pdo_sqlite_db_handle *H = (pdo_sqlite_db_handle *)dbh->driver_data;
	/* unregister functions, so that they don't linger for the next
	 * request */
	if (H) {
		pdo_sqlite_cleanup_callbacks(H);
	}
}