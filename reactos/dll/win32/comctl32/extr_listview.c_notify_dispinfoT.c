#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int mask; int cchTextMax; scalar_t__* pszText; } ;
struct TYPE_10__ {scalar_t__ code; } ;
struct TYPE_9__ {scalar_t__ notifyFormat; } ;
struct TYPE_8__ {TYPE_7__ item; TYPE_4__ hdr; } ;
typedef  scalar_t__* LPWSTR ;
typedef  char* LPSTR ;
typedef  TYPE_1__* LPNMLVDISPINFOW ;
typedef  char* LPCSTR ;
typedef  TYPE_2__ LISTVIEW_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__* Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int FALSE ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int LVIF_TEXT ; 
 scalar_t__ LVN_GETDISPINFOA ; 
 scalar_t__ LVN_GETDISPINFOW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__*,int) ; 
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ debuglvitem_t (TYPE_7__*,int) ; 
 scalar_t__ get_ansi_notification (scalar_t__) ; 
 scalar_t__ is_text (scalar_t__*) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__*,scalar_t__*) ; 
 int notify_hdr (TYPE_2__ const*,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static BOOL notify_dispinfoT(const LISTVIEW_INFO *infoPtr, UINT code, LPNMLVDISPINFOW pdi, BOOL isW)
{
    INT length = 0, ret_length;
    LPWSTR buffer = NULL, ret_text;
    BOOL return_ansi = FALSE;
    BOOL return_unicode = FALSE;
    BOOL ret;

    if ((pdi->item.mask & LVIF_TEXT) && is_text(pdi->item.pszText))
    {
	return_unicode = ( isW && infoPtr->notifyFormat == NFR_ANSI);
	return_ansi    = (!isW && infoPtr->notifyFormat == NFR_UNICODE);
    }

    ret_length = pdi->item.cchTextMax;
    ret_text = pdi->item.pszText;

    if (return_unicode || return_ansi)
    {
        if (code != LVN_GETDISPINFOW)
        {
            length = return_ansi ?
       		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pdi->item.pszText, -1, NULL, 0):
       		WideCharToMultiByte(CP_ACP, 0, pdi->item.pszText, -1, NULL, 0, NULL, NULL);
        }
        else
        {
            length = pdi->item.cchTextMax;
            *pdi->item.pszText = 0; /* make sure we don't process garbage */
        }

        buffer = Alloc( (return_ansi ? sizeof(WCHAR) : sizeof(CHAR)) * length);
        if (!buffer) return FALSE;

        if (return_ansi)
            MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pdi->item.pszText, -1,
	                        buffer, length);
        else
            WideCharToMultiByte(CP_ACP, 0, pdi->item.pszText, -1, (LPSTR) buffer,
	                        length, NULL, NULL);

        pdi->item.pszText = buffer;
        pdi->item.cchTextMax = length;
    }

    if (infoPtr->notifyFormat == NFR_ANSI)
        code = get_ansi_notification(code);

    TRACE(" pdi->item=%s\n", debuglvitem_t(&pdi->item, infoPtr->notifyFormat != NFR_ANSI));
    ret = notify_hdr(infoPtr, code, &pdi->hdr);
    TRACE(" resulting code=%d\n", pdi->hdr.code);

    if (return_ansi || return_unicode)
    {
        if (return_ansi && (pdi->hdr.code == LVN_GETDISPINFOA))
        {
            strcpy((char*)ret_text, (char*)pdi->item.pszText);
        }
        else if (return_unicode && (pdi->hdr.code == LVN_GETDISPINFOW))
        {
            lstrcpyW(ret_text, pdi->item.pszText);
        }
        else if (return_ansi) /* note : pointer can be changed by app ! */
        {
	    WideCharToMultiByte(CP_ACP, 0, pdi->item.pszText, -1, (LPSTR) ret_text,
                ret_length, NULL, NULL);
        }
        else
            MultiByteToWideChar(CP_ACP, 0, (LPSTR) pdi->item.pszText, -1,
                ret_text, ret_length);

        pdi->item.pszText = ret_text; /* restores our buffer */
        pdi->item.cchTextMax = ret_length;

        Free(buffer);
        return ret;
    }

    /* if dispinfo holder changed notification code then convert */
    if (!isW && (pdi->hdr.code == LVN_GETDISPINFOW) && (pdi->item.mask & LVIF_TEXT))
    {
        length = WideCharToMultiByte(CP_ACP, 0, pdi->item.pszText, -1, NULL, 0, NULL, NULL);

        buffer = Alloc(length * sizeof(CHAR));
        if (!buffer) return FALSE;

        WideCharToMultiByte(CP_ACP, 0, pdi->item.pszText, -1, (LPSTR) buffer,
                ret_length, NULL, NULL);

        strcpy((LPSTR)pdi->item.pszText, (LPSTR)buffer);
        Free(buffer);
    }

    return ret;
}