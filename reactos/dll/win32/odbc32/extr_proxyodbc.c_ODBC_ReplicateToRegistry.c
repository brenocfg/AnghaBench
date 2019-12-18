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
typedef  scalar_t__ SQLRETURN ;
typedef  int /*<<< orphan*/  SQLHENV ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ODBC32_SQLAllocEnv (int /*<<< orphan*/ *) ; 
 scalar_t__ ODBC32_SQLFreeEnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ODBC_ReplicateODBCInstToRegistry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ODBC_ReplicateODBCToRegistry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SQL_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static void ODBC_ReplicateToRegistry (void)
{
    SQLRETURN sql_ret;
    SQLHENV hEnv;

    if ((sql_ret = ODBC32_SQLAllocEnv (&hEnv)) == SQL_SUCCESS)
    {
        ODBC_ReplicateODBCInstToRegistry (hEnv);
        ODBC_ReplicateODBCToRegistry (FALSE /* system dsns */, hEnv);
        ODBC_ReplicateODBCToRegistry (TRUE /* user dsns */, hEnv);

        if ((sql_ret = ODBC32_SQLFreeEnv (hEnv)) != SQL_SUCCESS)
        {
            TRACE ("Error %d freeing the SQL environment.\n", (int)sql_ret);
        }
    }
    else
    {
        TRACE ("Error %d opening an SQL environment.\n", (int)sql_ret);
        WARN ("The external ODBC settings have not been replicated to the"
                " Wine registry\n");
    }
}