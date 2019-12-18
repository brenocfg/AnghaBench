#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int wDefault; void* wOutputOffset; void* wDeviceOffset; void* wDriverOffset; } ;
typedef  void* LPWSTR ;
typedef  TYPE_1__* LPDEVNAMES ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DEVNAMES ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GetDefaultPrinterW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,long) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalReAlloc (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lstrcpyW (void*,int /*<<< orphan*/  const*) ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/  const*,char) ; 

__attribute__((used)) static BOOL PRINTDLG_CreateDevNamesW(HGLOBAL *hmem, LPCWSTR DeviceDriverName,
				    LPCWSTR DeviceName, LPCWSTR OutputPort)
{
    long size;
    LPWSTR   pDevNamesSpace;
    LPWSTR   pTempPtr;
    LPDEVNAMES lpDevNames;
    WCHAR bufW[260];
    DWORD dwBufLen = ARRAY_SIZE(bufW);
    const WCHAR *p;

    p = wcsrchr( DeviceDriverName, '\\' );
    if (p) DeviceDriverName = p + 1;

    size = sizeof(WCHAR)*lstrlenW(DeviceDriverName) + 2
            + sizeof(WCHAR)*lstrlenW(DeviceName) + 2
            + sizeof(WCHAR)*lstrlenW(OutputPort) + 2
            + sizeof(DEVNAMES);

    if(*hmem)
        *hmem = GlobalReAlloc(*hmem, size, GMEM_MOVEABLE);
    else
        *hmem = GlobalAlloc(GMEM_MOVEABLE, size);
    if (*hmem == 0)
        return FALSE;

    pDevNamesSpace = GlobalLock(*hmem);
    lpDevNames = (LPDEVNAMES) pDevNamesSpace;

    pTempPtr = (LPWSTR)((LPDEVNAMES)pDevNamesSpace + 1);
    lstrcpyW(pTempPtr, DeviceDriverName);
    lpDevNames->wDriverOffset = pTempPtr - pDevNamesSpace;

    pTempPtr += lstrlenW(DeviceDriverName) + 1;
    lstrcpyW(pTempPtr, DeviceName);
    lpDevNames->wDeviceOffset = pTempPtr - pDevNamesSpace;

    pTempPtr += lstrlenW(DeviceName) + 1;
    lstrcpyW(pTempPtr, OutputPort);
    lpDevNames->wOutputOffset = pTempPtr - pDevNamesSpace;

    GetDefaultPrinterW(bufW, &dwBufLen);
    lpDevNames->wDefault = (lstrcmpW(bufW, DeviceName) == 0) ? 1 : 0;
    GlobalUnlock(*hmem);
    return TRUE;
}