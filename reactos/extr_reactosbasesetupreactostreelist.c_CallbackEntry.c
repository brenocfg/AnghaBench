#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_12__ {int /*<<< orphan*/  hWnd; scalar_t__* cTempText1; scalar_t__* cTempText2; } ;
typedef  TYPE_3__ TreeListData ;
struct TYPE_14__ {int uState; scalar_t__ iTextPixels; int /*<<< orphan*/  bFlags; int /*<<< orphan*/  uFirstChild; int /*<<< orphan*/  lParam; } ;
struct TYPE_11__ {unsigned int mask; int state; int stateMask; int iImage; int iSelectedImage; int cChildren; int cchTextMax; scalar_t__* pszText; scalar_t__ hItem; int /*<<< orphan*/  lParam; } ;
struct TYPE_10__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  hwndFrom; int /*<<< orphan*/  code; } ;
struct TYPE_13__ {TYPE_2__ item; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_4__ NMTVDISPINFO ;
typedef  scalar_t__* LPCTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HTREEITEM ;
typedef  TYPE_5__ BaseItem ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_ID ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I_CHILDRENCALLBACK ; 
 void* I_IMAGECALLBACK ; 
 int /*<<< orphan*/  LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int TVIF_CHILDREN ; 
 unsigned int TVIF_HANDLE ; 
 unsigned int TVIF_IMAGE ; 
 unsigned int TVIF_PARAM ; 
 unsigned int TVIF_SELECTEDIMAGE ; 
 unsigned int TVIF_STATE ; 
 unsigned int TVIF_TEXT ; 
 int TVIS_SELECTED ; 
 int /*<<< orphan*/  TVIX_HASBUTTON ; 
 int /*<<< orphan*/  TVIX_VARBUTTON ; 
 int /*<<< orphan*/  TVN_GETDISPINFO ; 
 int /*<<< orphan*/  UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 unsigned int str_len (scalar_t__*) ; 

__attribute__((used)) static void CallbackEntry(TreeListData *pData, BaseItem *pEntry, unsigned uItem, unsigned uFlags, int *iImage, unsigned *uTextSize, LPCTSTR *pText) {

	NMTVDISPINFO	sInfo;

	sInfo.item.mask				= TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | uFlags;
	sInfo.item.lParam			= pEntry->lParam;
	sInfo.item.hItem			= (HTREEITEM)(ULONG_PTR)uItem;
	sInfo.item.state			= pEntry->uState;
	sInfo.item.stateMask		= 0xFFFFFFFF;
	sInfo.item.iImage			= I_IMAGECALLBACK;
	sInfo.item.iSelectedImage	= I_IMAGECALLBACK;
	sInfo.item.cChildren		= I_CHILDRENCALLBACK;

	if(uFlags & TVIF_TEXT) {
		if(*uTextSize) {
			pData->cTempText2[sizeof(pData->cTempText2) / sizeof(TCHAR) - 1]	= 0;
			pData->cTempText2[0]	= 0;
			sInfo.item.pszText		= pData->cTempText2;
			sInfo.item.cchTextMax	= sizeof(pData->cTempText2) / sizeof(TCHAR) - 1;
		} else {
			pData->cTempText1[sizeof(pData->cTempText1) / sizeof(TCHAR) - 1]	= 0;
			pData->cTempText1[0]	= 0;
			sInfo.item.pszText		= pData->cTempText1;
			sInfo.item.cchTextMax	= sizeof(pData->cTempText1) / sizeof(TCHAR) - 1;
		}
	} else {
		sInfo.item.pszText		= 0;
		sInfo.item.cchTextMax	= 0;
	}

	sInfo.hdr.hwndFrom	= pData->hWnd;
	sInfo.hdr.idFrom	= GetWindowLong(pData->hWnd, GWL_ID);
	sInfo.hdr.code		= TVN_GETDISPINFO;

	UNLOCK(pData);
	SendMessage(GetParent(sInfo.hdr.hwndFrom), WM_NOTIFY, sInfo.hdr.idFrom, (LPARAM)&sInfo);
	LOCK(pData);

	if(uFlags & TVIF_IMAGE) {
		if(!(pEntry->uState & TVIS_SELECTED))
			*iImage = sInfo.item.iImage;
	} else
		if(uFlags & TVIF_SELECTEDIMAGE) {
			if(pEntry->uState & TVIS_SELECTED)
				*iImage = sInfo.item.iSelectedImage;
		}

	if(uFlags & TVIF_CHILDREN) {
		switch(sInfo.item.cChildren) {
			case  0:
				pEntry->bFlags    &= ~TVIX_HASBUTTON;
				pEntry->bFlags    |=  TVIX_VARBUTTON;
				break;

			case  1:
				pEntry->bFlags    &= ~TVIX_VARBUTTON;
				pEntry->bFlags    |=  TVIX_HASBUTTON;
				break;

			default
					:
				pEntry->bFlags    |=  TVIX_VARBUTTON;

				if(pEntry->uFirstChild)
					pEntry->bFlags |=  TVIX_HASBUTTON;
				else
					pEntry->bFlags &= ~TVIX_HASBUTTON;
		}
	}

	if(uFlags & TVIF_TEXT) {
		*pText		= sInfo.item.pszText;
		*uTextSize	= str_len(sInfo.item.pszText);
		pEntry->iTextPixels = 0;
	}

}