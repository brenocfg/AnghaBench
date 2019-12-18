#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * pszText; } ;
struct TYPE_10__ {scalar_t__ notifyFormat; int /*<<< orphan*/  hwndNotify; } ;
struct TYPE_7__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; } ;
struct TYPE_9__ {TYPE_2__* pitem; TYPE_1__ hdr; } ;
struct TYPE_8__ {int mask; scalar_t__ type; scalar_t__ pvFilter; int /*<<< orphan*/ * pszText; } ;
typedef  int /*<<< orphan*/  NMHEADERW ;
typedef  TYPE_3__ NMHEADERA ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* LPSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  TYPE_5__ HD_TEXTFILTERA ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ HDFT_ISSTRING ; 
 int HDI_FILTER ; 
 int HDI_TEXT ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrWtoA (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/  get_ansi_notification (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT notify_forward_header(const LISTVIEW_INFO *infoPtr, NMHEADERW *lpnmhW)
{
    LPCWSTR text = NULL, filter = NULL;
    LRESULT ret;
    NMHEADERA *lpnmh = (NMHEADERA*) lpnmhW;

    /* on unicode format exit earlier */
    if (infoPtr->notifyFormat == NFR_UNICODE)
        return SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, lpnmh->hdr.idFrom,
                            (LPARAM)lpnmh);

    /* header always supplies unicode notifications,
       all we have to do is to convert strings to ANSI */
    if (lpnmh->pitem)
    {
        /* convert item text */
        if (lpnmh->pitem->mask & HDI_TEXT)
        {
            text = (LPCWSTR)lpnmh->pitem->pszText;
            lpnmh->pitem->pszText = NULL;
            Str_SetPtrWtoA(&lpnmh->pitem->pszText, text);
        }
        /* convert filter text */
        if ((lpnmh->pitem->mask & HDI_FILTER) && (lpnmh->pitem->type == HDFT_ISSTRING) &&
             lpnmh->pitem->pvFilter)
        {
            filter = (LPCWSTR)((HD_TEXTFILTERA*)lpnmh->pitem->pvFilter)->pszText;
            ((HD_TEXTFILTERA*)lpnmh->pitem->pvFilter)->pszText = NULL;
            Str_SetPtrWtoA(&((HD_TEXTFILTERA*)lpnmh->pitem->pvFilter)->pszText, filter);
        }
    }
    lpnmh->hdr.code = get_ansi_notification(lpnmh->hdr.code);

    ret = SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, lpnmh->hdr.idFrom,
                       (LPARAM)lpnmh);

    /* cleanup */
    if(text)
    {
        Free(lpnmh->pitem->pszText);
        lpnmh->pitem->pszText = (LPSTR)text;
    }
    if(filter)
    {
        Free(((HD_TEXTFILTERA*)lpnmh->pitem->pvFilter)->pszText);
        ((HD_TEXTFILTERA*)lpnmh->pitem->pvFilter)->pszText = (LPSTR)filter;
    }

    return ret;
}