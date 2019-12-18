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
struct TYPE_3__ {int Flags; int /*<<< orphan*/  lpstrFindWhat; } ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  TYPE_1__ FINDREPLACE ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int FR_MATCHCASE ; 
 int FR_WHOLEWORD ; 
 int /*<<< orphan*/  _istspace (int /*<<< orphan*/ ) ; 
 size_t _tcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  _tcsnicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static BOOL
NOTEPAD_FindTextAt(FINDREPLACE *pFindReplace, LPCTSTR pszText, int iTextLength, DWORD dwPosition)
{
    BOOL bMatches;
    size_t iTargetLength;

    if ((!pFindReplace) || (!pszText))
    {
        return FALSE;
    }

    iTargetLength = _tcslen(pFindReplace->lpstrFindWhat);

    /* Make proper comparison */
    if (pFindReplace->Flags & FR_MATCHCASE)
        bMatches = !_tcsncmp(&pszText[dwPosition], pFindReplace->lpstrFindWhat, iTargetLength);
    else
        bMatches = !_tcsnicmp(&pszText[dwPosition], pFindReplace->lpstrFindWhat, iTargetLength);

    if (bMatches && pFindReplace->Flags & FR_WHOLEWORD)
    {
        if ((dwPosition > 0) && !_istspace(pszText[dwPosition-1]))
            bMatches = FALSE;
        if ((dwPosition < (DWORD) iTextLength - 1) && !_istspace(pszText[dwPosition+1]))
            bMatches = FALSE;
    }

    return bMatches;
}