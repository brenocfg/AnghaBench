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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* PWCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int GetLongestChildKeyName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,size_t,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PWCHAR GetNthChildKeyName( HANDLE RegHandle, DWORD n ) {
  LONG Status;
  int MaxAdapterName = GetLongestChildKeyName( RegHandle );
  PWCHAR Value;
  DWORD ValueLen;

  if (MaxAdapterName == -1)
    return 0;

  ValueLen = MaxAdapterName;
  Value = (PWCHAR)HeapAlloc( GetProcessHeap(), 0, MaxAdapterName * sizeof(WCHAR) );
  if (!Value) return 0;

  Status = RegEnumKeyExW( RegHandle, n, Value, &ValueLen,
			  NULL, NULL, NULL, NULL );
  if (Status != ERROR_SUCCESS) {
    HeapFree(GetProcessHeap(), 0, Value);
    return 0;
  } else {
    Value[ValueLen] = 0;
    return Value;
  }
}