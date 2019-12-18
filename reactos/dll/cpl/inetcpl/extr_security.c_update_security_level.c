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
struct TYPE_3__ {scalar_t__* levels; scalar_t__ last_level; int /*<<< orphan*/  htb; int /*<<< orphan*/  hsec; } ;
typedef  TYPE_1__ secdlg_data ;
typedef  scalar_t__ WCHAR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SEC_LEVEL ; 
 int /*<<< orphan*/  IDC_SEC_LEVEL_INFO ; 
 int IDS_SEC_LEVEL0 ; 
 size_t IDS_SEC_LEVEL0_INFO ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 int NUM_TRACKBAR_POS ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_NORMAL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_SETPOS ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  hcpl ; 
 size_t index_from_urltemplate (scalar_t__) ; 

__attribute__((used)) static void update_security_level(secdlg_data *sd, DWORD lv_index, DWORD tb_index)
{
    WCHAR name[512];
    DWORD current_index;

    TRACE("(%p, lv_index: %u, tb_index: %u)\n", sd, lv_index, tb_index);

    if ((sd->levels[lv_index] != sd->last_level) || (tb_index > 0)) {
        /* show or hide the trackbar */
        if (!sd->levels[lv_index] || !sd->last_level)
            ShowWindow(sd->htb, sd->levels[lv_index] ? SW_NORMAL : SW_HIDE);

        current_index = (tb_index > 0) ? tb_index : index_from_urltemplate(sd->levels[lv_index]);

        name[0] = 0;
        LoadStringW(hcpl, IDS_SEC_LEVEL0 + current_index, name, ARRAY_SIZE(name));
        TRACE("new level #%d: %s\n", current_index, debugstr_w(name));
        SetWindowTextW(GetDlgItem(sd->hsec, IDC_SEC_LEVEL), name);

        name[0] = 0;
        LoadStringW(hcpl, IDS_SEC_LEVEL0_INFO + (current_index * 0x10), name, ARRAY_SIZE(name));
        TRACE("new level info: %s\n", debugstr_w(name));
        SetWindowTextW(GetDlgItem(sd->hsec, IDC_SEC_LEVEL_INFO), name);

        if (current_index)
            SendMessageW(sd->htb, TBM_SETPOS, TRUE, NUM_TRACKBAR_POS - current_index);

        sd->last_level = sd->levels[lv_index];

    }
}