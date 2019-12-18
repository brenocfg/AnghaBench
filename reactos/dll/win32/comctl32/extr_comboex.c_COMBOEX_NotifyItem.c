#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ NtfUnicode; } ;
struct TYPE_7__ {scalar_t__ pszText; int mask; } ;
struct TYPE_8__ {TYPE_1__ ceItem; int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  TYPE_2__ NMCOMBOBOXEXW ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPSTR ;
typedef  int INT ;
typedef  TYPE_3__ COMBOEX_INFO ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ Alloc (int) ; 
 int CBEIF_TEXT ; 
 scalar_t__ CBEN_DRAGBEGINA ; 
 scalar_t__ CBEN_DRAGBEGINW ; 
 scalar_t__ CBEN_ENDEDITA ; 
 scalar_t__ CBEN_ENDEDITW ; 
 scalar_t__ CBEN_GETDISPINFOA ; 
 scalar_t__ CBEN_GETDISPINFOW ; 
 int COMBOEX_Notify (TYPE_3__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  Free (scalar_t__) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_textW (scalar_t__) ; 

__attribute__((used)) static INT
COMBOEX_NotifyItem (const COMBOEX_INFO *infoPtr, UINT code, NMCOMBOBOXEXW *hdr)
{
    /* Change the Text item from Unicode to ANSI if necessary for NOTIFY */
    if (infoPtr->NtfUnicode)
	return COMBOEX_Notify (infoPtr, code, &hdr->hdr);
    else {
	LPWSTR wstr = hdr->ceItem.pszText;
	LPSTR astr = 0;
	INT ret, len = 0;

	if ((hdr->ceItem.mask & CBEIF_TEXT) && is_textW(wstr)) {
	    len = WideCharToMultiByte (CP_ACP, 0, wstr, -1, 0, 0, NULL, NULL);
	    if (len > 0) {
                astr = Alloc ((len + 1)*sizeof(CHAR));
		if (!astr) return 0;
		WideCharToMultiByte (CP_ACP, 0, wstr, -1, astr, len, 0, 0);
		hdr->ceItem.pszText = (LPWSTR)astr;
	    }
	}

	if (code == CBEN_ENDEDITW) code = CBEN_ENDEDITA;
	else if (code == CBEN_GETDISPINFOW) code = CBEN_GETDISPINFOA;
	else if (code == CBEN_DRAGBEGINW) code = CBEN_DRAGBEGINA;

	ret = COMBOEX_Notify (infoPtr, code, (NMHDR *)hdr);

	if (astr && hdr->ceItem.pszText == (LPWSTR)astr)
	    hdr->ceItem.pszText = wstr;

	Free(astr);

	return ret;
    }
}