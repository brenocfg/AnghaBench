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
struct TYPE_7__ {int mask; scalar_t__ pszText; } ;
struct TYPE_6__ {scalar_t__ nNotifyFormat; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_1__ HEADER_INFO ;
typedef  TYPE_2__ HDITEMW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int HDI_TEXT ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  Str_SetPtrAtoW (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrWtoA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HEADER_CopyHDItemForNotify(const HEADER_INFO *infoPtr, HDITEMW *dest,
    const HDITEMW *src, BOOL fSourceUnicode, LPVOID *ppvScratch)
{
    *ppvScratch = NULL;
    *dest = *src;
    
    if (src->mask & HDI_TEXT && src->pszText != LPSTR_TEXTCALLBACKW) /* covers TEXTCALLBACKA as well */
    {
        if (fSourceUnicode && infoPtr->nNotifyFormat != NFR_UNICODE)
        {
            dest->pszText = NULL;
            Str_SetPtrWtoA((LPSTR *)&dest->pszText, src->pszText);
            *ppvScratch = dest->pszText;
        }
        
        if (!fSourceUnicode && infoPtr->nNotifyFormat == NFR_UNICODE)
        {
            dest->pszText = NULL;
            Str_SetPtrAtoW(&dest->pszText, (LPSTR)src->pszText);
            *ppvScratch = dest->pszText;
        }
    }
}