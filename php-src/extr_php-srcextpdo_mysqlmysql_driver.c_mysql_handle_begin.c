#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 scalar_t__ mysql_handle_doer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mysql_handle_begin(pdo_dbh_t *dbh)
{
	PDO_DBG_ENTER("mysql_handle_quoter");
	PDO_DBG_INF_FMT("dbh=%p", dbh);
	PDO_DBG_RETURN(0 <= mysql_handle_doer(dbh, ZEND_STRL("START TRANSACTION")));
}