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
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* heap_alloc (int) ; 
 int /*<<< orphan*/  hhctrl_hinstance ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LPWSTR HH_LoadString(DWORD dwID)
{
    LPWSTR string = NULL;
    LPCWSTR stringresource;
    int iSize;

    iSize = LoadStringW(hhctrl_hinstance, dwID, (LPWSTR)&stringresource, 0);

    string = heap_alloc((iSize + 2) * sizeof(WCHAR)); /* some strings (tab text) needs double-null termination */
    memcpy(string, stringresource, iSize*sizeof(WCHAR));
    string[iSize] = 0;

    return string;
}