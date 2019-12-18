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
typedef  int /*<<< orphan*/  desc ;
typedef  int /*<<< orphan*/  SQLUSMALLINT ;
typedef  scalar_t__ SQLSMALLINT ;
typedef  scalar_t__ SQLRETURN ;
typedef  int /*<<< orphan*/  SQLHENV ;
typedef  int /*<<< orphan*/  SQLCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 scalar_t__ ODBC32_SQLDrivers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SQL_FETCH_FIRST ; 
 int /*<<< orphan*/  SQL_FETCH_NEXT ; 
 scalar_t__ SQL_NO_DATA ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ lstrlenA (char*) ; 

__attribute__((used)) static void ODBC_ReplicateODBCInstToRegistry (SQLHENV hEnv)
{
    HKEY hODBCInst;
    LONG reg_ret;
    BOOL success;

    success = FALSE;
    TRACE ("Driver settings are not currently replicated to the registry\n");
    if ((reg_ret = RegCreateKeyExA (HKEY_LOCAL_MACHINE,
            "Software\\ODBC\\ODBCINST.INI", 0, NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS /* a couple more than we need */, NULL,
            &hODBCInst, NULL)) == ERROR_SUCCESS)
    {
        HKEY hDrivers;
        if ((reg_ret = RegCreateKeyExA (hODBCInst, "ODBC Drivers", 0,
                NULL, REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS /* overkill */, NULL, &hDrivers, NULL))
                == ERROR_SUCCESS)
        {
            SQLRETURN sql_ret;
            SQLUSMALLINT dirn;
            CHAR desc [256];
            SQLSMALLINT sizedesc;

            success = TRUE;
            dirn = SQL_FETCH_FIRST;
            while ((sql_ret = ODBC32_SQLDrivers (hEnv, dirn, (SQLCHAR*)desc, sizeof(desc),
                    &sizedesc, NULL, 0, NULL)) == SQL_SUCCESS ||
                    sql_ret == SQL_SUCCESS_WITH_INFO)
            {
                /* FIXME Do some proper handling of the SUCCESS_WITH_INFO */
                dirn = SQL_FETCH_NEXT;
                if (sizedesc == lstrlenA(desc))
                {
                    HKEY hThis;
                    if ((reg_ret = RegQueryValueExA (hDrivers, desc, NULL,
                            NULL, NULL, NULL)) == ERROR_FILE_NOT_FOUND)
                    {
                        if ((reg_ret = RegSetValueExA (hDrivers, desc, 0,
                                REG_SZ, (const BYTE *)"Installed", 10)) != ERROR_SUCCESS)
                        {
                            TRACE ("Error %d replicating driver %s\n",
                                    reg_ret, desc);
                            success = FALSE;
                        }
                    }
                    else if (reg_ret != ERROR_SUCCESS)
                    {
                        TRACE ("Error %d checking for %s in drivers\n",
                                reg_ret, desc);
                        success = FALSE;
                    }
                    if ((reg_ret = RegCreateKeyExA (hODBCInst, desc, 0,
                            NULL, REG_OPTION_NON_VOLATILE,
                            KEY_ALL_ACCESS, NULL, &hThis, NULL))
                            == ERROR_SUCCESS)
                    {
                        /* FIXME This is where the settings go.
                         * I suggest that if the disposition says it 
                         * exists then we leave it alone.  Alternatively
                         * include an extra value to flag that it is 
                         * a replication of the unixODBC/iODBC/...
                         */
                        if ((reg_ret = RegCloseKey (hThis)) !=
                                ERROR_SUCCESS)
                            TRACE ("Error %d closing %s key\n", reg_ret,
                                    desc);
                    }
                    else
                    {
                        TRACE ("Error %d ensuring driver key %s\n",
                                reg_ret, desc);
                        success = FALSE;
                    }
                }
                else
                {
                    WARN ("Unusually long driver name %s not replicated\n",
                            desc);
                    success = FALSE;
                }
            }
            if (sql_ret != SQL_NO_DATA)
            {
                TRACE ("Error %d enumerating drivers\n", (int)sql_ret);
                success = FALSE;
            }
            if ((reg_ret = RegCloseKey (hDrivers)) != ERROR_SUCCESS)
            {
                TRACE ("Error %d closing hDrivers\n", reg_ret);
            }
        }
        else
        {
            TRACE ("Error %d opening HKLM\\S\\O\\OI\\Drivers\n", reg_ret);
        }
        if ((reg_ret = RegCloseKey (hODBCInst)) != ERROR_SUCCESS)
        {
            TRACE ("Error %d closing HKLM\\S\\O\\ODBCINST.INI\n", reg_ret);
        }
    }
    else
    {
        TRACE ("Error %d opening HKLM\\S\\O\\ODBCINST.INI\n", reg_ret);
    }
    if (!success)
    {
        WARN ("May not have replicated all ODBC drivers to the registry\n");
    }
}