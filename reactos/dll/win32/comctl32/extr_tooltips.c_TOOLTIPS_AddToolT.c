#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int uNumTools; scalar_t__ hwndSelf; TYPE_1__* tools; } ;
struct TYPE_10__ {int uFlags; scalar_t__ cbSize; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; scalar_t__ uId; int /*<<< orphan*/  hwnd; } ;
struct TYPE_9__ {int uFlags; int uInternalFlags; void* bNotifyUnicode; int /*<<< orphan*/  hwnd; scalar_t__ uId; int /*<<< orphan*/  lParam; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  rect; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TTTOOLINFOW ;
typedef  TYPE_3__ TOOLTIPS_INFO ;
typedef  void* LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 void* FALSE ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ IS_INTRESOURCE (int /*<<< orphan*/ *) ; 
 int LOWORD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int NFR_ANSI ; 
 int NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowSubclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TOOLTIPS_IsCallbackString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TOOLTIPS_SubclassProc ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 int TTF_IDISHWND ; 
 int TTF_SUBCLASS ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 
 scalar_t__ TTTOOLINFOW_V2_SIZE ; 
 scalar_t__ TTTOOLINFOW_V3_SIZE ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 
 int debugstr_a (char*) ; 
 int debugstr_w (int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_AddToolT (TOOLTIPS_INFO *infoPtr, const TTTOOLINFOW *ti, BOOL isW)
{
    TTTOOL_INFO *toolPtr;
    INT nResult;

    if (!ti) return FALSE;

    TRACE("add tool (%p) %p %ld%s\n", infoPtr->hwndSelf, ti->hwnd, ti->uId,
        (ti->uFlags & TTF_IDISHWND) ? " TTF_IDISHWND" : "");

    if (ti->cbSize > TTTOOLINFOW_V3_SIZE && isW)
        return FALSE;

    if (infoPtr->uNumTools == 0) {
	infoPtr->tools = Alloc (sizeof(TTTOOL_INFO));
	toolPtr = infoPtr->tools;
    }
    else {
	TTTOOL_INFO *oldTools = infoPtr->tools;
	infoPtr->tools =
	    Alloc (sizeof(TTTOOL_INFO) * (infoPtr->uNumTools + 1));
	memcpy (infoPtr->tools, oldTools,
		infoPtr->uNumTools * sizeof(TTTOOL_INFO));
	Free (oldTools);
	toolPtr = &infoPtr->tools[infoPtr->uNumTools];
    }

    infoPtr->uNumTools++;

    /* copy tool data */
    toolPtr->uFlags         = ti->uFlags;
    toolPtr->uInternalFlags = (ti->uFlags & (TTF_SUBCLASS | TTF_IDISHWND));
    toolPtr->hwnd           = ti->hwnd;
    toolPtr->uId            = ti->uId;
    toolPtr->rect           = ti->rect;
    toolPtr->hinst          = ti->hinst;

    if (ti->cbSize >= TTTOOLINFOW_V1_SIZE) {
        if (IS_INTRESOURCE(ti->lpszText)) {
            TRACE("add string id %x\n", LOWORD(ti->lpszText));
            toolPtr->lpszText = ti->lpszText;
        }
        else if (ti->lpszText) {
            if (TOOLTIPS_IsCallbackString(ti->lpszText, isW)) {
                TRACE("add CALLBACK\n");
                toolPtr->lpszText = LPSTR_TEXTCALLBACKW;
            }
            else if (isW) {
                INT len = lstrlenW (ti->lpszText);
                TRACE("add text %s\n", debugstr_w(ti->lpszText));
                toolPtr->lpszText =	Alloc ((len + 1)*sizeof(WCHAR));
                strcpyW (toolPtr->lpszText, ti->lpszText);
            }
            else {
                INT len = MultiByteToWideChar(CP_ACP, 0, (LPSTR)ti->lpszText, -1, NULL, 0);
                TRACE("add text \"%s\"\n", debugstr_a((char *)ti->lpszText));
                toolPtr->lpszText =	Alloc (len * sizeof(WCHAR));
                MultiByteToWideChar(CP_ACP, 0, (LPSTR)ti->lpszText, -1, toolPtr->lpszText, len);
            }
        }
    }

    if (ti->cbSize >= TTTOOLINFOW_V2_SIZE)
	toolPtr->lParam = ti->lParam;

    /* install subclassing hook */
    if (toolPtr->uInternalFlags & TTF_SUBCLASS) {
	if (toolPtr->uInternalFlags & TTF_IDISHWND) {
	    SetWindowSubclass((HWND)toolPtr->uId, TOOLTIPS_SubclassProc, 1,
			      (DWORD_PTR)infoPtr->hwndSelf);
	}
	else {
	    SetWindowSubclass(toolPtr->hwnd, TOOLTIPS_SubclassProc, 1,
			      (DWORD_PTR)infoPtr->hwndSelf);
	}
	TRACE("subclassing installed\n");
    }

    nResult = SendMessageW (toolPtr->hwnd, WM_NOTIFYFORMAT,
                            (WPARAM)infoPtr->hwndSelf, NF_QUERY);
    if (nResult == NFR_ANSI) {
        toolPtr->bNotifyUnicode = FALSE;
	TRACE(" -- WM_NOTIFYFORMAT returns: NFR_ANSI\n");
    } else if (nResult == NFR_UNICODE) {
        toolPtr->bNotifyUnicode = TRUE;
	TRACE(" -- WM_NOTIFYFORMAT returns: NFR_UNICODE\n");
    } else {
        TRACE (" -- WM_NOTIFYFORMAT returns: %d\n", nResult);
    }

    return TRUE;
}