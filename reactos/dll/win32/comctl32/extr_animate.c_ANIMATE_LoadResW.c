#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mminfo ;
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  hRes; int /*<<< orphan*/  hMMio; } ;
struct TYPE_6__ {int /*<<< orphan*/  cchBuffer; scalar_t__ pchBuffer; int /*<<< orphan*/  fccIOProc; } ;
typedef  TYPE_1__ MMIOINFO ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FOURCC_MEM ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  FreeResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_READ ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmioOpenW (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL ANIMATE_LoadResW(ANIMATE_INFO *infoPtr, HINSTANCE hInst, LPCWSTR lpName)
{
    static const WCHAR aviW[] = { 'A', 'V', 'I', 0 };
    HRSRC 	hrsrc;
    MMIOINFO	mminfo;
    LPVOID	lpAvi;

    hrsrc = FindResourceW(hInst, lpName, aviW);
    if (!hrsrc)
	return FALSE;

    infoPtr->hRes = LoadResource(hInst, hrsrc);
    if (!infoPtr->hRes)
 	return FALSE;

    lpAvi = LockResource(infoPtr->hRes);
    if (!lpAvi)
	return FALSE;

    memset(&mminfo, 0, sizeof(mminfo));
    mminfo.fccIOProc = FOURCC_MEM;
    mminfo.pchBuffer = lpAvi;
    mminfo.cchBuffer = SizeofResource(hInst, hrsrc);
    infoPtr->hMMio = mmioOpenW(NULL, &mminfo, MMIO_READ);
    if (!infoPtr->hMMio) 
    {
	FreeResource(infoPtr->hRes);
	return FALSE;
    }

    return TRUE;
}