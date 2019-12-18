#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int flags; char* psz; } ;
struct TYPE_12__ {scalar_t__ nItemCount; scalar_t__ lastKeyPressTimestamp; int nSearchParamLength; char* szSearchParam; char charCode; int nFocusedItem; int dwStyle; } ;
struct TYPE_11__ {int iItem; int cchTextMax; int /*<<< orphan*/ * pszText; scalar_t__ iSubItem; int /*<<< orphan*/  mask; } ;
struct TYPE_10__ {int iStart; int /*<<< orphan*/  hdr; TYPE_5__ lvfi; } ;
typedef  TYPE_1__ NMLVFINDITEMW ;
typedef  TYPE_2__ LVITEMW ;
typedef  int /*<<< orphan*/  LPNMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ LISTVIEW_INFO ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetTickCount () ; 
 scalar_t__ KEY_DELAY ; 
 int /*<<< orphan*/  LISTVIEW_GetItemW (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  LISTVIEW_KeySelection (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int LVFI_PARTIAL ; 
 int LVFI_WRAP ; 
 int /*<<< orphan*/  LVIF_TEXT ; 
 int /*<<< orphan*/  LVN_ODFINDITEMW ; 
 int LVS_OWNERDATA ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  iswalnum (char) ; 
 int /*<<< orphan*/  lstrncmpiW (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ notify_hdr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT LISTVIEW_ProcessLetterKeys(LISTVIEW_INFO *infoPtr, WPARAM charCode, LPARAM keyData)
{
    WCHAR buffer[MAX_PATH];
    DWORD prevTime;
    LVITEMW item;
    int startidx;
    INT nItem;
    INT diff;

    /* simple parameter checking */
    if (!charCode || !keyData || infoPtr->nItemCount == 0) return 0;

    /* only allow the valid WM_CHARs through */
    if (!iswalnum(charCode) &&
        charCode != '.' && charCode != '`' && charCode != '!' &&
        charCode != '@' && charCode != '#' && charCode != '$' &&
        charCode != '%' && charCode != '^' && charCode != '&' &&
        charCode != '*' && charCode != '(' && charCode != ')' &&
        charCode != '-' && charCode != '_' && charCode != '+' &&
        charCode != '=' && charCode != '\\'&& charCode != ']' &&
        charCode != '}' && charCode != '[' && charCode != '{' &&
        charCode != '/' && charCode != '?' && charCode != '>' &&
        charCode != '<' && charCode != ',' && charCode != '~')
        return 0;

    /* update the search parameters */
    prevTime = infoPtr->lastKeyPressTimestamp;
    infoPtr->lastKeyPressTimestamp = GetTickCount();
    diff = infoPtr->lastKeyPressTimestamp - prevTime;

    if (diff >= 0 && diff < KEY_DELAY)
    {
        if (infoPtr->nSearchParamLength < MAX_PATH - 1)
            infoPtr->szSearchParam[infoPtr->nSearchParamLength++] = charCode;

        if (infoPtr->charCode != charCode)
            infoPtr->charCode = charCode = 0;
    }
    else
    {
        infoPtr->charCode = charCode;
        infoPtr->szSearchParam[0] = charCode;
        infoPtr->nSearchParamLength = 1;
    }

    /* should start from next after focused item, so next item that matches
       will be selected, if there isn't any and focused matches it will be selected
       on second search stage from beginning of the list */
    if (infoPtr->nFocusedItem >= 0 && infoPtr->nItemCount > 1)
    {
        /* with some accumulated search data available start with current focus, otherwise
           it's excluded from search */
        startidx = infoPtr->nSearchParamLength > 1 ? infoPtr->nFocusedItem : infoPtr->nFocusedItem + 1;
        if (startidx == infoPtr->nItemCount) startidx = 0;
    }
    else
        startidx = 0;

    /* let application handle this for virtual listview */
    if (infoPtr->dwStyle & LVS_OWNERDATA)
    {
        NMLVFINDITEMW nmlv;

        memset(&nmlv.lvfi, 0, sizeof(nmlv.lvfi));
        nmlv.lvfi.flags = (LVFI_WRAP | LVFI_PARTIAL);
        nmlv.lvfi.psz = infoPtr->szSearchParam;
        nmlv.iStart = startidx;

        infoPtr->szSearchParam[infoPtr->nSearchParamLength] = 0;

        nItem = notify_hdr(infoPtr, LVN_ODFINDITEMW, (LPNMHDR)&nmlv.hdr);
    }
    else
    {
        int i = startidx, endidx;

        /* and search from the current position */
        nItem = -1;
        endidx = infoPtr->nItemCount;

        /* first search in [startidx, endidx), on failure continue in [0, startidx) */
        while (1)
        {
            /* start from first item if not found with >= startidx */
            if (i == infoPtr->nItemCount && startidx > 0)
            {
                endidx = startidx;
                startidx = 0;
            }

            for (i = startidx; i < endidx; i++)
            {
                /* retrieve text */
                item.mask = LVIF_TEXT;
                item.iItem = i;
                item.iSubItem = 0;
                item.pszText = buffer;
                item.cchTextMax = MAX_PATH;
                if (!LISTVIEW_GetItemW(infoPtr, &item)) return 0;

                if (!lstrncmpiW(item.pszText, infoPtr->szSearchParam, infoPtr->nSearchParamLength))
                {
                    nItem = i;
                    break;
                }
                /* this is used to find first char match when search string is not available yet,
                   otherwise every WM_CHAR will search to next item by first char, ignoring that we're
                   already waiting for user to complete a string */
                else if (nItem == -1 && infoPtr->nSearchParamLength == 1 && !lstrncmpiW(item.pszText, infoPtr->szSearchParam, 1))
                {
                    /* this would work but we must keep looking for a longer match */
                    nItem = i;
                }
            }

            if ( nItem != -1 || /* found something */
                 endidx != infoPtr->nItemCount || /* second search done */
                (startidx == 0 && endidx == infoPtr->nItemCount) /* full range for first search */ )
                break;
        };
    }

    if (nItem != -1)
        LISTVIEW_KeySelection(infoPtr, nItem, FALSE);

    return 0;
}