#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  hwndSelf; TYPE_1__* tools; } ;
struct TYPE_8__ {scalar_t__ lpszText; scalar_t__ bNotifyUnicode; int /*<<< orphan*/  hinst; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFOTIPSIZE ; 
 scalar_t__ IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_GetDispInfoA (TYPE_2__ const*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TOOLTIPS_GetDispInfoW (TYPE_2__ const*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int TTS_NOPREFIX ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* strchrW (char*,char) ; 

__attribute__((used)) static void
TOOLTIPS_GetTipText (const TOOLTIPS_INFO *infoPtr, INT nTool, WCHAR *buffer)
{
    TTTOOL_INFO *toolPtr = &infoPtr->tools[nTool];

    if (IS_INTRESOURCE(toolPtr->lpszText)) {
	/* load a resource */
	TRACE("load res string %p %x\n",
	       toolPtr->hinst, LOWORD(toolPtr->lpszText));
	if (!LoadStringW (toolPtr->hinst, LOWORD(toolPtr->lpszText), buffer, INFOTIPSIZE))
	    buffer[0] = '\0';
    }
    else if (toolPtr->lpszText) {
	if (toolPtr->lpszText == LPSTR_TEXTCALLBACKW) {
	    if (toolPtr->bNotifyUnicode)
		TOOLTIPS_GetDispInfoW(infoPtr, toolPtr, buffer);
	    else
		TOOLTIPS_GetDispInfoA(infoPtr, toolPtr, buffer);
	}
	else {
	    /* the item is a usual (unicode) text */
	    lstrcpynW (buffer, toolPtr->lpszText, INFOTIPSIZE);
	}
    }
    else {
	/* no text available */
        buffer[0] = '\0';
    }

    if (!(GetWindowLongW(infoPtr->hwndSelf, GWL_STYLE) & TTS_NOPREFIX)) {
        WCHAR *ptrW;
        if ((ptrW = strchrW(buffer, '\t')))
            *ptrW = 0;
    }

    TRACE("%s\n", debugstr_w(buffer));
}