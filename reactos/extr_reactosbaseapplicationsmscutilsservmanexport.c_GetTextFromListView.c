#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
struct TYPE_6__ {int cchTextMax; int /*<<< orphan*/  pszText; void* iSubItem; int /*<<< orphan*/  mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  hListView; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  TYPE_2__ LVITEM ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  void* INT ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LVIF_TEXT ; 
 int /*<<< orphan*/  LVM_GETITEMTEXTW ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static DWORD
GetTextFromListView(PMAIN_WND_INFO Info,
                    LPWSTR Text,
                    INT row,
                    INT col)
{
    LVITEM item;
    DWORD NumChars;

    ZeroMemory(&item, sizeof(item));
    item.mask = LVIF_TEXT;
    item.iSubItem = col;
    item.pszText = Text;
    item.cchTextMax = 500;
    NumChars = (INT)SendMessageW(Info->hListView,
                                 LVM_GETITEMTEXTW,
                                 row,
                                 (LPARAM)&item);
    return NumChars;
}