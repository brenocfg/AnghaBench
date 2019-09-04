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
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 scalar_t__ dbcmd (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dbsqlexec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_dblib_transaction_cmd(const char *cmd, pdo_dbh_t *dbh)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;

	if (FAIL == dbcmd(H->link, cmd)) {
		return 0;
	}

	if (FAIL == dbsqlexec(H->link)) {
		return 0;
	}

	return 1;
}