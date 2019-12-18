#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  char WCHAR ;
struct TYPE_13__ {scalar_t__ hIcon; int /*<<< orphan*/  pszIcon; } ;
struct TYPE_10__ {scalar_t__ pszTemplate; int /*<<< orphan*/ * pResource; } ;
struct TYPE_16__ {int dwFlags; char* pszTitle; TYPE_4__ u2; int /*<<< orphan*/  hInstance; TYPE_1__ u; scalar_t__ pfnCallback; } ;
struct TYPE_15__ {int signature; } ;
struct TYPE_11__ {int dwFlags; } ;
struct TYPE_14__ {int width; int height; scalar_t__ hImageList; TYPE_3__* proppage; TYPE_2__ ppshheader; void* hasHelp; } ;
struct TYPE_12__ {int useCallback; int hasHelp; int hasIcon; int const* pszText; void* isDirty; scalar_t__ hwndPage; scalar_t__ hpage; } ;
typedef  TYPE_5__ PropSheetInfo ;
typedef  TYPE_6__ MyDLGTEMPLATEEX ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_7__* LPCPROPSHEETPAGEW ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  scalar_t__ HPROPSHEETPAGE ;
typedef  scalar_t__ HICON ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DLGTEMPLATE ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FindResourceA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILC_COLOR ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 scalar_t__ IS_INTRESOURCE (char*) ; 
 int /*<<< orphan*/  ImageList_AddIcon (scalar_t__,scalar_t__) ; 
 scalar_t__ ImageList_Create (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LockResource (int /*<<< orphan*/ ) ; 
 int PSH_HEADER ; 
 int PSH_WIZARD ; 
 int PSH_WIZARD97_NEW ; 
 int PSH_WIZARD97_OLD ; 
 int PSP_DLGINDIRECT ; 
 int PSP_HASHELP ; 
 int PSP_HIDEHEADER ; 
 int PSP_INTERNAL_UNICODE ; 
 int PSP_USECALLBACK ; 
 int PSP_USEHEADERSUBTITLE ; 
 int PSP_USEHEADERTITLE ; 
 int PSP_USEHICON ; 
 int PSP_USEICONID ; 
 int PSP_USETITLE ; 
 scalar_t__ RT_DIALOG ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 scalar_t__ WIZARD_HEADER_HEIGHT ; 
 int WIZARD_PADDING ; 
 int /*<<< orphan*/  debugstr_w (int const*) ; 
 int const* heap_strdupW (char const*) ; 
 int /*<<< orphan*/  lstrlenW (int const*) ; 

__attribute__((used)) static BOOL PROPSHEET_CollectPageInfo(LPCPROPSHEETPAGEW lppsp,
                               PropSheetInfo * psInfo,
                               int index, BOOL resize)
{
  const DLGTEMPLATE* pTemplate;
  const WORD*  p;
  DWORD dwFlags;
  int width, height;

  if (!lppsp)
    return FALSE;

  TRACE("\n");
  psInfo->proppage[index].hpage = (HPROPSHEETPAGE)lppsp;
  psInfo->proppage[index].hwndPage = 0;
  psInfo->proppage[index].isDirty = FALSE;

  /*
   * Process property page flags.
   */
  dwFlags = lppsp->dwFlags;
  psInfo->proppage[index].useCallback = (dwFlags & PSP_USECALLBACK) && (lppsp->pfnCallback);
  psInfo->proppage[index].hasHelp = dwFlags & PSP_HASHELP;
  psInfo->proppage[index].hasIcon = dwFlags & (PSP_USEHICON | PSP_USEICONID);

  /* as soon as we have a page with the help flag, set the sheet flag on */
  if (psInfo->proppage[index].hasHelp)
    psInfo->hasHelp = TRUE;

  /*
   * Process page template.
   */
  if (dwFlags & PSP_DLGINDIRECT)
    pTemplate = lppsp->u.pResource;
  else if(dwFlags & PSP_INTERNAL_UNICODE )
  {
    HRSRC hResource = FindResourceW(lppsp->hInstance,
                                    lppsp->u.pszTemplate,
                                    (LPWSTR)RT_DIALOG);
    HGLOBAL hTemplate = LoadResource(lppsp->hInstance,
                                     hResource);
    pTemplate = LockResource(hTemplate);
  }
  else
  {
    HRSRC hResource = FindResourceA(lppsp->hInstance,
                                    (LPCSTR)lppsp->u.pszTemplate,
                                    (LPSTR)RT_DIALOG);
    HGLOBAL hTemplate = LoadResource(lppsp->hInstance,
                                     hResource);
    pTemplate = LockResource(hTemplate);
  }

  /*
   * Extract the size of the page and the caption.
   */
  if (!pTemplate)
      return FALSE;

  p = (const WORD *)pTemplate;

  if (((const MyDLGTEMPLATEEX*)pTemplate)->signature == 0xFFFF)
  {
    /* DLGTEMPLATEEX (not defined in any std. header file) */

    p++;       /* dlgVer    */
    p++;       /* signature */
    p += 2;    /* help ID   */
    p += 2;    /* ext style */
    p += 2;    /* style     */
  }
  else
  {
    /* DLGTEMPLATE */

    p += 2;    /* style     */
    p += 2;    /* ext style */
  }

  p++;    /* nb items */
  p++;    /*   x      */
  p++;    /*   y      */
  width  = (WORD)*p; p++;
  height = (WORD)*p; p++;

  if (lppsp->dwFlags & (PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE))
    psInfo->ppshheader.dwFlags |= PSH_HEADER;

  /* Special calculation for interior wizard pages so the largest page is
   * calculated correctly. We need to add all the padding and space occupied
   * by the header so the width and height sums up to the whole wizard client
   * area. */
  if ((psInfo->ppshheader.dwFlags & (PSH_WIZARD97_OLD | PSH_WIZARD97_NEW)) &&
      (psInfo->ppshheader.dwFlags & PSH_HEADER) &&
      !(dwFlags & PSP_HIDEHEADER))
  {
      height += 2 * WIZARD_PADDING + WIZARD_HEADER_HEIGHT;
      width += 2 * WIZARD_PADDING;
  }
  if (psInfo->ppshheader.dwFlags & PSH_WIZARD)
  {
      height += 2 * WIZARD_PADDING;
      width += 2 * WIZARD_PADDING;
  }

  /* remember the largest width and height */
  if (resize)
  {
      if (width > psInfo->width)
        psInfo->width = width;

      if (height > psInfo->height)
        psInfo->height = height;
  }

  /* menu */
  switch ((WORD)*p)
  {
    case 0x0000:
      p++;
      break;
    case 0xffff:
      p += 2;
      break;
    default:
      p += lstrlenW( p ) + 1;
      break;
  }

  /* class */
  switch ((WORD)*p)
  {
    case 0x0000:
      p++;
      break;
    case 0xffff:
      p += 2;
      break;
    default:
      p += lstrlenW( p ) + 1;
      break;
  }

  /* Extract the caption */
  psInfo->proppage[index].pszText = p;
  TRACE("Tab %d %s\n",index,debugstr_w( p ));

  if (dwFlags & PSP_USETITLE)
  {
    WCHAR szTitle[256];
    const WCHAR *pTitle;
    static const WCHAR pszNull[] = { '(','n','u','l','l',')',0 };

    if (IS_INTRESOURCE( lppsp->pszTitle ))
    {
      if (LoadStringW( lppsp->hInstance, (DWORD_PTR)lppsp->pszTitle, szTitle, ARRAY_SIZE(szTitle)))
        pTitle = szTitle;
      else if (*p)
        pTitle = p;
      else
        pTitle = pszNull;
    }
    else
      pTitle = lppsp->pszTitle;

    psInfo->proppage[index].pszText = heap_strdupW( pTitle );
  }

  /*
   * Build the image list for icons
   */
  if ((dwFlags & PSP_USEHICON) || (dwFlags & PSP_USEICONID))
  {
    HICON hIcon;
    int icon_cx = GetSystemMetrics(SM_CXSMICON);
    int icon_cy = GetSystemMetrics(SM_CYSMICON);

    if (dwFlags & PSP_USEICONID)
      hIcon = LoadImageW(lppsp->hInstance, lppsp->u2.pszIcon, IMAGE_ICON,
                         icon_cx, icon_cy, LR_DEFAULTCOLOR);
    else
      hIcon = lppsp->u2.hIcon;

    if ( hIcon )
    {
      if (psInfo->hImageList == 0 )
	psInfo->hImageList = ImageList_Create(icon_cx, icon_cy, ILC_COLOR, 1, 1);

      ImageList_AddIcon(psInfo->hImageList, hIcon);
    }

  }

  return TRUE;
}