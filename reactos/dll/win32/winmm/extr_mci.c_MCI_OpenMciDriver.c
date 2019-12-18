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
typedef  int /*<<< orphan*/  libName ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * hDriver; } ;
typedef  TYPE_1__* LPWINE_MCIDRIVER ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HDRVR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_GetLibName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ DRIVER_TryOpenDriver32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  wszMci ; 

__attribute__((used)) static	BOOL	MCI_OpenMciDriver(LPWINE_MCIDRIVER wmd, LPCWSTR drvTyp, DWORD_PTR lp)
{
    WCHAR	libName[128];

    if (!DRIVER_GetLibName(drvTyp, wszMci, libName, sizeof(libName)))
	return FALSE;

    /* First load driver */
    wmd->hDriver = (HDRVR)DRIVER_TryOpenDriver32(libName, lp);
    return wmd->hDriver != NULL;
}