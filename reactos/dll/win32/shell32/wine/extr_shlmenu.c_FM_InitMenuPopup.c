#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_8__ {int bInitialized; int uID; int uEnumFlags; scalar_t__ pidl; int /*<<< orphan*/  (* lpfnCallback ) (scalar_t__,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int cbSize; scalar_t__ dwMenuData; void* fMask; } ;
typedef  TYPE_1__ MENUINFO ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  (* LPFNFMCALLBACK ) (scalar_t__,int /*<<< orphan*/ *) ;
typedef  TYPE_2__* LPFMINFO ;
typedef  scalar_t__ LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IEnumIDList ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  FMINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePopupMenu () ; 
 int /*<<< orphan*/  ERR (char*,TYPE_2__*,int) ; 
 int FALSE ; 
 int FM_BLANK_ICON ; 
 int /*<<< orphan*/  FM_DEFAULT_HEIGHT ; 
 int /*<<< orphan*/  FileMenu_AppendItemW (int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenuInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetMenuItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IEnumIDList_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumIDList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 scalar_t__ ILCombine (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILGDN_FORPARSING ; 
 int /*<<< orphan*/  ILGetDisplayNameExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellFolder_BindToObject (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IShellFolder_GetAttributesOf (int /*<<< orphan*/ *,int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 void* MIM_MENUDATA ; 
 scalar_t__* PathFindExtensionW (char*) ; 
 int /*<<< orphan*/  PidlToSicIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int SFGAO_FOLDER ; 
 int SHCONTF_FOLDERS ; 
 int SHCONTF_NONFOLDERS ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetMenuInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  bAbortInit ; 

__attribute__((used)) static int FM_InitMenuPopup(HMENU hmenu, LPCITEMIDLIST pAlternatePidl)
{	IShellFolder	*lpsf, *lpsf2;
	ULONG		ulItemAttr = SFGAO_FOLDER;
	UINT		uID, uEnumFlags;
	LPFNFMCALLBACK	lpfnCallback;
	LPCITEMIDLIST	pidl;
	WCHAR		sTemp[MAX_PATH];
	int		NumberOfItems = 0, iIcon;
	MENUINFO	MenuInfo;
	LPFMINFO	menudata;

	TRACE("%p %p\n", hmenu, pAlternatePidl);

	MenuInfo.cbSize = sizeof(MENUINFO);
	MenuInfo.fMask = MIM_MENUDATA;

	if (! GetMenuInfo(hmenu, &MenuInfo))
	  return FALSE;

	menudata = (LPFMINFO)MenuInfo.dwMenuData;

	if ((menudata == 0) || (MenuInfo.cbSize != sizeof(MENUINFO)))
	{
	  ERR("menudata corrupt: %p %u\n", menudata, MenuInfo.cbSize);
	  return 0;
	}

	if (menudata->bInitialized)
	  return 0;

	pidl = (pAlternatePidl? pAlternatePidl: menudata->pidl);
	if (!pidl)
	  return 0;

	uID = menudata->uID;
	uEnumFlags = menudata->uEnumFlags;
	lpfnCallback = menudata->lpfnCallback;
	menudata->bInitialized = FALSE;

	SetMenuInfo(hmenu, &MenuInfo);

	if (SUCCEEDED (SHGetDesktopFolder(&lpsf)))
	{
	  if (SUCCEEDED(IShellFolder_BindToObject(lpsf, pidl,0,&IID_IShellFolder,(LPVOID *)&lpsf2)))
	  {
	    IEnumIDList	*lpe = NULL;

	    if (SUCCEEDED (IShellFolder_EnumObjects(lpsf2, 0, uEnumFlags, &lpe )))
	    {

	      LPITEMIDLIST pidlTemp = NULL;
	      ULONG ulFetched;

	      while ((!bAbortInit) && (S_OK == IEnumIDList_Next(lpe,1,&pidlTemp,&ulFetched)))
	      {
		if (SUCCEEDED (IShellFolder_GetAttributesOf(lpsf, 1, (LPCITEMIDLIST*)&pidlTemp, &ulItemAttr)))
		{
		  ILGetDisplayNameExW(NULL, pidlTemp, sTemp, ILGDN_FORPARSING);
		  if (! (PidlToSicIndex(lpsf, pidlTemp, FALSE, 0, &iIcon)))
		    iIcon = FM_BLANK_ICON;
		  if ( SFGAO_FOLDER & ulItemAttr)
		  {
		    LPFMINFO lpFmMi;
		    MENUINFO MenuInfo;
		    HMENU hMenuPopup = CreatePopupMenu();

		    lpFmMi = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(FMINFO));

		    lpFmMi->pidl = ILCombine(pidl, pidlTemp);
		    lpFmMi->uEnumFlags = SHCONTF_FOLDERS | SHCONTF_NONFOLDERS;

		    MenuInfo.cbSize = sizeof(MENUINFO);
		    MenuInfo.fMask = MIM_MENUDATA;
		    MenuInfo.dwMenuData = (ULONG_PTR) lpFmMi;
		    SetMenuInfo (hMenuPopup, &MenuInfo);

		    FileMenu_AppendItemW (hmenu, sTemp, uID, iIcon, hMenuPopup, FM_DEFAULT_HEIGHT);
		  }
		  else
		  {
		    LPWSTR pExt = PathFindExtensionW(sTemp);
		    if (pExt)
		      *pExt = 0;
		    FileMenu_AppendItemW (hmenu, sTemp, uID, iIcon, 0, FM_DEFAULT_HEIGHT);
		  }
		}

		if (lpfnCallback)
		{
		  TRACE("enter callback\n");
		  lpfnCallback ( pidl, pidlTemp);
		  TRACE("leave callback\n");
		}

		NumberOfItems++;
	      }
	      IEnumIDList_Release (lpe);
	    }
	    IShellFolder_Release(lpsf2);
	  }
	  IShellFolder_Release(lpsf);
	}

	if ( GetMenuItemCount (hmenu) == 0 )
	{
          static const WCHAR szEmpty[] = { '(','e','m','p','t','y',')',0 };
	  FileMenu_AppendItemW (hmenu, szEmpty, uID, FM_BLANK_ICON, 0, FM_DEFAULT_HEIGHT);
	  NumberOfItems++;
	}

	menudata->bInitialized = TRUE;
	SetMenuInfo(hmenu, &MenuInfo);

	return NumberOfItems;
}