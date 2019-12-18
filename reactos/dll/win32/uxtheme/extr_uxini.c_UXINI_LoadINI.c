#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UXINI_FILE ;
struct TYPE_4__ {void* lpEnd; void* lpCurLoc; void* lpIni; } ;
typedef  TYPE_1__* PUXINI_FILE ;
typedef  void* LPCWSTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  szTextFileResource ; 

PUXINI_FILE UXINI_LoadINI(HMODULE hTheme, LPCWSTR lpName) {
    HRSRC hrsc;
    LPCWSTR lpThemesIni = NULL;
    PUXINI_FILE uf;
    DWORD dwIniSize;

    TRACE("Loading resource INI %s\n", debugstr_w(lpName));

    if((hrsc = FindResourceW(hTheme, lpName, szTextFileResource))) {
        if(!(lpThemesIni = LoadResource(hTheme, hrsc))) {
            TRACE("%s resource not found\n", debugstr_w(lpName));
            return NULL;
        }
    }

    dwIniSize = SizeofResource(hTheme, hrsc) / sizeof(WCHAR);
    uf = HeapAlloc(GetProcessHeap(), 0, sizeof(UXINI_FILE));
    uf->lpIni = lpThemesIni;
    uf->lpCurLoc = lpThemesIni;
    uf->lpEnd = lpThemesIni + dwIniSize;
    return uf;
}