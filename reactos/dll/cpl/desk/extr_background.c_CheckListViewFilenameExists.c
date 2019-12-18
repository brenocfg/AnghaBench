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
struct TYPE_3__ {int /*<<< orphan*/  psz; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ LVFINDINFO ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LVFI_STRING ; 
 int ListView_FindItem (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
CheckListViewFilenameExists(HWND hwndList, LPCTSTR tszFileName)
{
    LVFINDINFO lvfi;
    int retVal;

    lvfi.flags = LVFI_STRING; /* Search item by EXACT string */
    lvfi.psz   = tszFileName; /* String to search */

    /* Other items of this structure are not valid, besacuse flags are not set. */
    retVal = ListView_FindItem(hwndList, -1, &lvfi);
    if (retVal != -1)
        return TRUE; /* item found! */

    return FALSE; /* item not found. */
}