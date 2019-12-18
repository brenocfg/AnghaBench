#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lvi ;
typedef  int WCHAR ;
struct TYPE_4__ {int* pszText; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ LVITEM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  LVIF_TEXT ; 
 int ListView_InsertItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ListView_SetItemText (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int     list_channel_CB(HANDLE hProcess, void* addr, WCHAR* buffer, void* user)
{
    int     j;
    WCHAR   val[2];
    LVITEM  lvi;
    int     index;
    HWND    hChannelLV = (HWND)user;

    memset(&lvi, 0, sizeof(lvi));

    lvi.mask = LVIF_TEXT;
    lvi.pszText = buffer + 1;

    index = ListView_InsertItem(hChannelLV, &lvi);
    if (index == -1) return 0;

    val[1] = L'\0';
    for (j = 0; j < 4; j++)
    {
        val[0] = (buffer[0] & (1 << j)) ? L'x' : L' ';
        ListView_SetItemText(hChannelLV, index, j + 1, val);
    }
    return 1;
}