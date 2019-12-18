#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hwndToolTip; int /*<<< orphan*/  Self; } ;
struct TYPE_4__ {int cbSize; char* lpszText; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOA ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  char CHAR ;

/* Variables and functions */
 int INFOTIPSIZE ; 
 int /*<<< orphan*/  SendMessageA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TTM_GETTEXTA ; 
 int /*<<< orphan*/  lstrcpynA (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
STATUSBAR_GetTipTextA (const STATUS_INFO *infoPtr, INT id, LPSTR tip, INT size)
{
    TRACE("\n");
    if (tip) {
        CHAR buf[INFOTIPSIZE];
        buf[0]='\0';

        if (infoPtr->hwndToolTip) {
            TTTOOLINFOA ti;
            ti.cbSize = sizeof(TTTOOLINFOA);
            ti.hwnd = infoPtr->Self;
            ti.uId = id;
            ti.lpszText = buf;
            SendMessageA (infoPtr->hwndToolTip, TTM_GETTEXTA, 0, (LPARAM)&ti);
        }
        lstrcpynA (tip, buf, size);
    }
    return 0;
}