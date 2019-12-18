#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct detail_data {int dummy; } ;
typedef  int /*<<< orphan*/  create_detailed_value_func ;
struct TYPE_2__ {int mask; int iItem; int iSubItem; void* pszText; scalar_t__ lParam; } ;
typedef  TYPE_1__ LVITEMW ;
typedef  void* LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int LVIF_PARAM ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  LVM_GETITEMCOUNT ; 
 int /*<<< orphan*/  LVM_INSERTITEMW ; 
 int /*<<< orphan*/  LVM_SETITEMTEXTW ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  add_field_value_data (struct detail_data*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void add_field_and_value_to_list(HWND hwnd, struct detail_data *data,
 LPWSTR field, LPWSTR value, create_detailed_value_func create, void *param)
{
    LVITEMW item;
    int iItem = SendMessageW(hwnd, LVM_GETITEMCOUNT, 0, 0);

    item.mask = LVIF_TEXT | LVIF_PARAM;
    item.iItem = iItem;
    item.iSubItem = 0;
    item.pszText = field;
    item.lParam = (LPARAM)data;
    SendMessageW(hwnd, LVM_INSERTITEMW, 0, (LPARAM)&item);
    if (value)
    {
        item.pszText = value;
        item.iSubItem = 1;
        SendMessageW(hwnd, LVM_SETITEMTEXTW, iItem, (LPARAM)&item);
    }
    add_field_value_data(data, create, param);
}