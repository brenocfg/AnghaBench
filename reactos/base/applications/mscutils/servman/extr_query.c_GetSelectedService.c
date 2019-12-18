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
struct TYPE_5__ {scalar_t__ lParam; int /*<<< orphan*/  iItem; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  hListView; int /*<<< orphan*/  SelectedItem; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  TYPE_2__ LVITEM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  ENUM_SERVICE_STATUS_PROCESS ;

/* Variables and functions */
 int /*<<< orphan*/  LVIF_PARAM ; 
 int /*<<< orphan*/  LVM_GETITEM ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ENUM_SERVICE_STATUS_PROCESS*
GetSelectedService(PMAIN_WND_INFO Info)
{
    LVITEM lvItem;

    lvItem.mask = LVIF_PARAM;
    lvItem.iItem = Info->SelectedItem;
    SendMessage(Info->hListView,
                LVM_GETITEM,
                0,
                (LPARAM)&lvItem);

    /* return pointer to selected service */
    return (ENUM_SERVICE_STATUS_PROCESS *)lvItem.lParam;
}