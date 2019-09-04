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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegInstallA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINE_MESSAGE (char*) ; 
 scalar_t__ check_native_ie () ; 

__attribute__((used)) static DWORD register_iexplore(BOOL doregister)
{
    HRESULT hres;

    if (check_native_ie()) {
        WINE_MESSAGE("Native IE detected, not doing registration\n");
        return 0;
    }

    hres = RegInstallA(NULL, doregister ? "RegisterIE" : "UnregisterIE", NULL);
    return FAILED(hres);
}