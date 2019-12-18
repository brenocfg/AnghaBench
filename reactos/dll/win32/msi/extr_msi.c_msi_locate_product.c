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
typedef  scalar_t__ MSIINSTALLCONTEXT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_UNKNOWN_PRODUCT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSIINSTALLCONTEXT_MACHINE ; 
 scalar_t__ MSIINSTALLCONTEXT_NONE ; 
 scalar_t__ MSIINSTALLCONTEXT_USERMANAGED ; 
 scalar_t__ MSIINSTALLCONTEXT_USERUNMANAGED ; 
 scalar_t__ MSIREG_OpenProductKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 

UINT msi_locate_product(LPCWSTR szProduct, MSIINSTALLCONTEXT *context)
{
    HKEY hkey = NULL;

    *context = MSIINSTALLCONTEXT_NONE;
    if (!szProduct) return ERROR_UNKNOWN_PRODUCT;

    if (MSIREG_OpenProductKey(szProduct, NULL, MSIINSTALLCONTEXT_USERMANAGED,
                              &hkey, FALSE) == ERROR_SUCCESS)
        *context = MSIINSTALLCONTEXT_USERMANAGED;
    else if (MSIREG_OpenProductKey(szProduct, NULL, MSIINSTALLCONTEXT_MACHINE,
                                   &hkey, FALSE) == ERROR_SUCCESS)
        *context = MSIINSTALLCONTEXT_MACHINE;
    else if (MSIREG_OpenProductKey(szProduct, NULL,
                                   MSIINSTALLCONTEXT_USERUNMANAGED,
                                   &hkey, FALSE) == ERROR_SUCCESS)
        *context = MSIINSTALLCONTEXT_USERUNMANAGED;

    RegCloseKey(hkey);

    if (*context == MSIINSTALLCONTEXT_NONE)
        return ERROR_UNKNOWN_PRODUCT;

    return ERROR_SUCCESS;
}