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
struct TYPE_5__ {int mask; scalar_t__ pszText; scalar_t__ lParam; scalar_t__ iSubItem; int /*<<< orphan*/  iItem; int /*<<< orphan*/  stateMask; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {scalar_t__ pwszName; } ;
typedef  TYPE_1__* PCCRYPT_OID_INFO ;
typedef  TYPE_2__ LVITEMW ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CheckBitmapIndex ;

/* Variables and functions */
 int /*<<< orphan*/  INDEXTOSTATEIMAGEMASK (int /*<<< orphan*/ ) ; 
 int LVIF_PARAM ; 
 int LVIF_STATE ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  LVIS_STATEIMAGEMASK ; 
 int /*<<< orphan*/  LVM_GETITEMCOUNT ; 
 int /*<<< orphan*/  LVM_INSERTITEMW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void add_known_usage(HWND lv, PCCRYPT_OID_INFO info,
 CheckBitmapIndex state)
{
    LVITEMW item;

    item.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM;
    item.state = INDEXTOSTATEIMAGEMASK(state);
    item.stateMask = LVIS_STATEIMAGEMASK;
    item.iItem = SendMessageW(lv, LVM_GETITEMCOUNT, 0, 0);
    item.iSubItem = 0;
    item.lParam = (LPARAM)info;
    item.pszText = (LPWSTR)info->pwszName;
    SendMessageW(lv, LVM_INSERTITEMW, 0, (LPARAM)&item);
}