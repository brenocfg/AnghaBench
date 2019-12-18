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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  db; int /*<<< orphan*/  platform; int /*<<< orphan*/  ProductCode; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSIREG_OpenUninstallKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  szInstalled ; 
 int /*<<< orphan*/  szOne ; 

__attribute__((used)) static UINT set_installed_prop( MSIPACKAGE *package )
{
    HKEY hkey;
    UINT r;

    if (!package->ProductCode) return ERROR_FUNCTION_FAILED;

    r = MSIREG_OpenUninstallKey( package->ProductCode, package->platform, &hkey, FALSE );
    if (r == ERROR_SUCCESS)
    {
        RegCloseKey( hkey );
        msi_set_property( package->db, szInstalled, szOne, -1 );
    }
    return r;
}