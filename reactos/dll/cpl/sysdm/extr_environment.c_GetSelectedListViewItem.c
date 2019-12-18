#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ LB_ERR ; 
 scalar_t__ LVIS_SELECTED ; 
 int /*<<< orphan*/  LVM_GETITEMCOUNT ; 
 int /*<<< orphan*/  LVM_GETITEMSTATE ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT
GetSelectedListViewItem(HWND hwndListView)
{
    INT iCount;
    INT iItem;

    iCount = SendMessage(hwndListView,
                         LVM_GETITEMCOUNT,
                         0,
                         0);
    if (iCount != LB_ERR)
    {
        for (iItem = 0; iItem < iCount; iItem++)
        {
            if (SendMessage(hwndListView,
                            LVM_GETITEMSTATE,
                            iItem,
                            (LPARAM) LVIS_SELECTED) == LVIS_SELECTED)
            {
                return iItem;
            }
        }
    }

    return -1;
}