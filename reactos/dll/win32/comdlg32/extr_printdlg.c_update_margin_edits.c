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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ edt4 ; 
 scalar_t__ edt7 ; 
 int /*<<< orphan*/ * element_from_margin_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pagesetup_get_margin_rect (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  size2str (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_margin_edits(HWND hDlg, const pagesetup_data *data, WORD id)
{
    WCHAR str[100];
    WORD idx;

    for(idx = edt4; idx <= edt7; idx++)
    {
        if(id == 0 || id == idx)
        {
            size2str(data, *element_from_margin_id(pagesetup_get_margin_rect(data), idx), str);
            SetDlgItemTextW(hDlg, idx, str);
        }
    }
}