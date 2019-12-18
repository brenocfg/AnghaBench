#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pszUrlJump2; int /*<<< orphan*/  pszUrlJump1; int /*<<< orphan*/  pszJump2; int /*<<< orphan*/  pszJump1; int /*<<< orphan*/  pszHome; int /*<<< orphan*/  pszCaption; int /*<<< orphan*/  pszIndex; int /*<<< orphan*/  pszToc; int /*<<< orphan*/  pszFile; int /*<<< orphan*/  pszType; } ;
struct TYPE_7__ {int fsValidMembers; int cbStruct; void* pszCustomTabs; void* pszUrlJump2; void* pszUrlJump1; void* pszJump2; void* pszJump1; void* pszHome; void* pszCaption; void* pszIndex; void* pszToc; void* pszFile; void* pszType; int /*<<< orphan*/  curNavType; int /*<<< orphan*/  cHistory; int /*<<< orphan*/  tabOrder; int /*<<< orphan*/  tabpos; int /*<<< orphan*/  fNotExpanded; int /*<<< orphan*/  fsToolBarFlags; int /*<<< orphan*/  paInfoTypes; int /*<<< orphan*/  nShowState; int /*<<< orphan*/  iNavWidth; int /*<<< orphan*/  rcWindowPos; int /*<<< orphan*/  dwExStyles; int /*<<< orphan*/  dwStyles; int /*<<< orphan*/  fsWinProperties; } ;
struct TYPE_8__ {int /*<<< orphan*/  pszCustomTabs; TYPE_1__ stringsW; TYPE_2__ WinType; } ;
typedef  TYPE_2__ HH_WINTYPEW ;
typedef  TYPE_3__ HHInfo ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int HHWIN_PARAM_CUR_TAB ; 
 int HHWIN_PARAM_EXPANSION ; 
 int HHWIN_PARAM_EXSTYLES ; 
 int HHWIN_PARAM_HISTORY_COUNT ; 
 int HHWIN_PARAM_INFOTYPES ; 
 int HHWIN_PARAM_NAV_WIDTH ; 
 int HHWIN_PARAM_PROPERTIES ; 
 int HHWIN_PARAM_RECT ; 
 int HHWIN_PARAM_SHOWSTATE ; 
 int HHWIN_PARAM_STYLES ; 
 int HHWIN_PARAM_TABORDER ; 
 int HHWIN_PARAM_TABPOS ; 
 int HHWIN_PARAM_TB_FLAGS ; 
 void* MergeChmString (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void MergeChmProperties(HH_WINTYPEW *src, HHInfo *info, BOOL override)
{
    DWORD unhandled_params = src->fsValidMembers & ~(HHWIN_PARAM_PROPERTIES|HHWIN_PARAM_STYLES
                             |HHWIN_PARAM_EXSTYLES|HHWIN_PARAM_RECT|HHWIN_PARAM_NAV_WIDTH
                             |HHWIN_PARAM_SHOWSTATE|HHWIN_PARAM_INFOTYPES|HHWIN_PARAM_TB_FLAGS
                             |HHWIN_PARAM_EXPANSION|HHWIN_PARAM_TABPOS|HHWIN_PARAM_TABORDER
                             |HHWIN_PARAM_HISTORY_COUNT|HHWIN_PARAM_CUR_TAB);
    HH_WINTYPEW *dst = &info->WinType;
    DWORD merge = override ? src->fsValidMembers : src->fsValidMembers & ~dst->fsValidMembers;

    if (unhandled_params)
        FIXME("Unsupported fsValidMembers fields: 0x%x\n", unhandled_params);

    dst->fsValidMembers |= merge;
    if (dst->cbStruct == 0)
    {
        /* If the structure has not been filled in yet then use all of the values */
        dst->cbStruct = sizeof(HH_WINTYPEW);
        merge = ~0;
    }
    if (merge & HHWIN_PARAM_PROPERTIES) dst->fsWinProperties = src->fsWinProperties;
    if (merge & HHWIN_PARAM_STYLES) dst->dwStyles = src->dwStyles;
    if (merge & HHWIN_PARAM_EXSTYLES) dst->dwExStyles = src->dwExStyles;
    if (merge & HHWIN_PARAM_RECT) dst->rcWindowPos = src->rcWindowPos;
    if (merge & HHWIN_PARAM_NAV_WIDTH) dst->iNavWidth = src->iNavWidth;
    if (merge & HHWIN_PARAM_SHOWSTATE) dst->nShowState = src->nShowState;
    if (merge & HHWIN_PARAM_INFOTYPES) dst->paInfoTypes = src->paInfoTypes;
    if (merge & HHWIN_PARAM_TB_FLAGS) dst->fsToolBarFlags = src->fsToolBarFlags;
    if (merge & HHWIN_PARAM_EXPANSION) dst->fNotExpanded = src->fNotExpanded;
    if (merge & HHWIN_PARAM_TABPOS) dst->tabpos = src->tabpos;
    if (merge & HHWIN_PARAM_TABORDER) memcpy(dst->tabOrder, src->tabOrder, sizeof(src->tabOrder));
    if (merge & HHWIN_PARAM_HISTORY_COUNT) dst->cHistory = src->cHistory;
    if (merge & HHWIN_PARAM_CUR_TAB) dst->curNavType = src->curNavType;

    /*
     * Note: We assume that hwndHelp, hwndCaller, hwndToolBar, hwndNavigation, and hwndHTML cannot be
     * modified by the user.  rcHTML and rcMinSize are not currently supported, so don't bother to copy them.
     */

    dst->pszType       = MergeChmString(src->pszType, &info->stringsW.pszType);
    dst->pszFile       = MergeChmString(src->pszFile, &info->stringsW.pszFile);
    dst->pszToc        = MergeChmString(src->pszToc, &info->stringsW.pszToc);
    dst->pszIndex      = MergeChmString(src->pszIndex, &info->stringsW.pszIndex);
    dst->pszCaption    = MergeChmString(src->pszCaption, &info->stringsW.pszCaption);
    dst->pszHome       = MergeChmString(src->pszHome, &info->stringsW.pszHome);
    dst->pszJump1      = MergeChmString(src->pszJump1, &info->stringsW.pszJump1);
    dst->pszJump2      = MergeChmString(src->pszJump2, &info->stringsW.pszJump2);
    dst->pszUrlJump1   = MergeChmString(src->pszUrlJump1, &info->stringsW.pszUrlJump1);
    dst->pszUrlJump2   = MergeChmString(src->pszUrlJump2, &info->stringsW.pszUrlJump2);

    /* FIXME: pszCustomTabs is a list of multiple zero-terminated strings so ReadString won't
     * work in this case
     */
#if 0
    dst->pszCustomTabs = MergeChmString(src->pszCustomTabs, &info->pszCustomTabs);
#endif
}