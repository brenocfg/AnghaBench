#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {scalar_t__ iImage; int /*<<< orphan*/  const* pszText; int /*<<< orphan*/  cxy; int /*<<< orphan*/  lParam; int /*<<< orphan*/  fmt; int /*<<< orphan*/  hbm; } ;
struct TYPE_5__ {scalar_t__ iImage; int callbackMask; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  cxy; int /*<<< orphan*/  lParam; int /*<<< orphan*/  fmt; int /*<<< orphan*/  hbm; } ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HDITEMW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int HDI_BITMAP ; 
 int HDI_FORMAT ; 
 int HDI_IMAGE ; 
 int HDI_LPARAM ; 
 int HDI_TEXT ; 
 int HDI_UNSUPPORTED_FIELDS ; 
 int HDI_WIDTH ; 
 scalar_t__ I_IMAGECALLBACK ; 
 int /*<<< orphan*/  const* LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  Str_SetPtrAtoW (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrW (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HEADER_StoreHDItemInHeader(HEADER_ITEM *lpItem, UINT mask, const HDITEMW *phdi, BOOL fUnicode)
{
    if (mask & HDI_UNSUPPORTED_FIELDS)
        FIXME("unsupported header fields %x\n", (mask & HDI_UNSUPPORTED_FIELDS));
    
    if (mask & HDI_BITMAP)
        lpItem->hbm = phdi->hbm;

    if (mask & HDI_FORMAT)
        lpItem->fmt = phdi->fmt;

    if (mask & HDI_LPARAM)
        lpItem->lParam = phdi->lParam;

    if (mask & HDI_WIDTH)
        lpItem->cxy = phdi->cxy;

    if (mask & HDI_IMAGE) 
    {
        lpItem->iImage = phdi->iImage;
        if (phdi->iImage == I_IMAGECALLBACK)
            lpItem->callbackMask |= HDI_IMAGE;
        else
            lpItem->callbackMask &= ~HDI_IMAGE;
    }

    if (mask & HDI_TEXT)
    {
        heap_free(lpItem->pszText);
        lpItem->pszText = NULL;

        if (phdi->pszText != LPSTR_TEXTCALLBACKW) /* covers != TEXTCALLBACKA too */
        {
            static const WCHAR emptyString[] = {0};

            LPCWSTR pszText = (phdi->pszText != NULL ? phdi->pszText : emptyString);
            if (fUnicode)
                Str_SetPtrW(&lpItem->pszText, pszText);
            else
                Str_SetPtrAtoW(&lpItem->pszText, (LPCSTR)pszText);
            lpItem->callbackMask &= ~HDI_TEXT;
        }
        else
        {
            lpItem->pszText = NULL;
            lpItem->callbackMask |= HDI_TEXT;
        }  
    }
}