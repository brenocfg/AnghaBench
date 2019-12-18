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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSISIGNATURE ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ACTION_AppSearchComponents (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ACTION_AppSearchDr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ACTION_AppSearchGetSignature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ACTION_AppSearchIni (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ACTION_AppSearchReg (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 

__attribute__((used)) static UINT ACTION_AppSearchSigName(MSIPACKAGE *package, LPCWSTR sigName,
 MSISIGNATURE *sig, LPWSTR *appValue)
{
    UINT rc;

    *appValue = NULL;
    rc = ACTION_AppSearchGetSignature(package, sig, sigName);
    if (rc == ERROR_SUCCESS)
    {
        rc = ACTION_AppSearchComponents(package, appValue, sig);
        if (rc == ERROR_SUCCESS && !*appValue)
        {
            rc = ACTION_AppSearchReg(package, appValue, sig);
            if (rc == ERROR_SUCCESS && !*appValue)
            {
                rc = ACTION_AppSearchIni(package, appValue, sig);
                if (rc == ERROR_SUCCESS && !*appValue)
                    rc = ACTION_AppSearchDr(package, appValue, sig);
            }
        }
    }
    return rc;
}