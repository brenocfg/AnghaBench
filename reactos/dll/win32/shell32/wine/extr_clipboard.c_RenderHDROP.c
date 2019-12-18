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
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
struct TYPE_3__ {int pFiles; int /*<<< orphan*/  fWide; } ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  TYPE_1__ DROPFILES ;

/* Variables and functions */
 int GHND ; 
 int GMEM_SHARE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * GlobalAlloc (int,int) ; 
 TYPE_1__* GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILCombine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslashW (scalar_t__*) ; 
 int /*<<< orphan*/  SHGetPathFromIDListW (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ILSimpleGetTextW (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__*) ; 
 int strlenW (scalar_t__*) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,scalar_t__*) ; 
 int wcslen (scalar_t__*) ; 

HGLOBAL RenderHDROP(LPITEMIDLIST pidlRoot, LPITEMIDLIST * apidl, UINT cidl)
{
	UINT i;
#ifdef __REACTOS__
        int size = 0;
#else
	int rootlen = 0,size = 0;
	WCHAR wszRootPath[MAX_PATH];
#endif
	WCHAR wszFileName[MAX_PATH];
	HGLOBAL hGlobal = NULL;
	DROPFILES *pDropFiles;
	int offset;
#ifdef __REACTOS__
        LPITEMIDLIST *pidls;
#endif

	TRACE("(%p,%p,%u)\n", pidlRoot, apidl, cidl);

#ifdef __REACTOS__
        pidls = (LPITEMIDLIST *)HeapAlloc(GetProcessHeap(), 0, cidl * sizeof(*pidls));
        if (!pidls)
            goto cleanup;
#endif

	/* get the size needed */
	size = sizeof(DROPFILES);

#ifndef __REACTOS__
	SHGetPathFromIDListW(pidlRoot, wszRootPath);
	PathAddBackslashW(wszRootPath);
	rootlen = strlenW(wszRootPath);
#endif

	for (i=0; i<cidl;i++)
	{
#ifdef __REACTOS__
          pidls[i] = ILCombine(pidlRoot, apidl[i]);
          SHGetPathFromIDListW(pidls[i], wszFileName);
          size += (wcslen(wszFileName) + 1) * sizeof(WCHAR);
#else
	  _ILSimpleGetTextW(apidl[i], wszFileName, MAX_PATH);
	  size += (rootlen + strlenW(wszFileName) + 1) * sizeof(WCHAR);
#endif
	}

	size += sizeof(WCHAR);

	/* Fill the structure */
	hGlobal = GlobalAlloc(GHND|GMEM_SHARE, size);
#ifdef __REACTOS__
        if(!hGlobal) goto cleanup;
#else
	if(!hGlobal) return hGlobal;
#endif

        pDropFiles = GlobalLock(hGlobal);
	offset = (sizeof(DROPFILES) + sizeof(WCHAR) - 1) / sizeof(WCHAR);
        pDropFiles->pFiles = offset * sizeof(WCHAR);
        pDropFiles->fWide = TRUE;

#ifndef __REACTOS__
	strcpyW(wszFileName, wszRootPath);
#endif

	for (i=0; i<cidl;i++)
	{

#ifdef __REACTOS__
          SHGetPathFromIDListW(pidls[i], wszFileName);
          wcscpy(((WCHAR*)pDropFiles)+offset, wszFileName);
          offset += wcslen(wszFileName) + 1;
          ILFree(pidls[i]);
#else
	  _ILSimpleGetTextW(apidl[i], wszFileName + rootlen, MAX_PATH - rootlen);
	  strcpyW(((WCHAR*)pDropFiles)+offset, wszFileName);
	  offset += strlenW(wszFileName) + 1;
#endif
	}

	((WCHAR*)pDropFiles)[offset] = 0;
	GlobalUnlock(hGlobal);

#ifdef __REACTOS__
cleanup:
    if(pidls)
        HeapFree(GetProcessHeap(), 0, pidls);
#endif

	return hGlobal;
}