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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int bNtfUnicode; scalar_t__ hwnd; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 scalar_t__ NF_REQUERY ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static INT TREEVIEW_NotifyFormat (TREEVIEW_INFO *infoPtr, HWND hwndFrom, UINT nCommand)
{
    INT format;

    TRACE("(hwndFrom=%p, nCommand=%d)\n", hwndFrom, nCommand);

    if (nCommand != NF_REQUERY) return 0;

    format = SendMessageW(hwndFrom, WM_NOTIFYFORMAT, (WPARAM)infoPtr->hwnd, NF_QUERY);
    TRACE("format=%d\n", format);

    /* Invalid format returned by NF_QUERY defaults to ANSI*/
    if (format != NFR_ANSI && format != NFR_UNICODE)
        format = NFR_ANSI;

    infoPtr->bNtfUnicode = (format == NFR_UNICODE);

    return format;
}