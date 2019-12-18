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
struct detail_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* add ) (int /*<<< orphan*/ ,struct detail_data*) ;} ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_DETAIL_LIST ; 
 int /*<<< orphan*/  LVM_DELETEALLITEMS ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* listItems ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct detail_data*) ; 

__attribute__((used)) static void set_fields_selection(HWND hwnd, struct detail_data *data, int sel)
{
    HWND list = GetDlgItem(hwnd, IDC_DETAIL_LIST);

    if (sel >= 0 && sel < ARRAY_SIZE(listItems))
    {
        SendMessageW(list, LVM_DELETEALLITEMS, 0, 0);
        listItems[sel].add(list, data);
    }
}