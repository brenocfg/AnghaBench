#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int VARTYPE ;
struct TYPE_6__ {int /*<<< orphan*/  pszVal; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
struct TYPE_7__ {int wYear; int wMonth; int wDay; int wHour; int wMinute; int wSecond; int wMilliseconds; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ PROPVARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
#define  VT_LPSTR 128 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static HRESULT PROPVAR_ConvertFILETIME(const FILETIME *ft, PROPVARIANT *ppropvarDest, VARTYPE vt)
{
    SYSTEMTIME time;

    FileTimeToSystemTime(ft, &time);

    switch (vt)
    {
        case VT_LPSTR:
            ppropvarDest->u.pszVal = HeapAlloc(GetProcessHeap(), 0, 64);
            if (!ppropvarDest->u.pszVal)
                return E_OUTOFMEMORY;

            sprintf( ppropvarDest->u.pszVal, "%04d/%02d/%02d:%02d:%02d:%02d.%03d",
                      time.wYear, time.wMonth, time.wDay,
                      time.wHour, time.wMinute, time.wSecond,
                      time.wMilliseconds );

            return S_OK;

        default:
            FIXME("Unhandled target type: %d\n", vt);
    }

    return E_FAIL;
}