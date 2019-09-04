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
struct TYPE_5__ {size_t last_lv_index; int /*<<< orphan*/  hsec; TYPE_2__* zone_attr; } ;
typedef  TYPE_1__ secdlg_data ;
struct TYPE_6__ {int /*<<< orphan*/  szDisplayName; int /*<<< orphan*/ * szDescription; } ;
typedef  TYPE_2__ ZONEATTRIBUTES ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SEC_GROUP ; 
 int /*<<< orphan*/  IDC_SEC_ZONE_INFO ; 
 int /*<<< orphan*/  IDS_SEC_SETTINGS ; 
 size_t LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcpl ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  update_security_level (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_zone_info(secdlg_data *sd, DWORD lv_index)
{
    ZONEATTRIBUTES *za = &sd->zone_attr[lv_index];
    WCHAR name[MAX_PATH];
    DWORD len;

    SetWindowTextW(GetDlgItem(sd->hsec, IDC_SEC_ZONE_INFO), za->szDescription);

    len = LoadStringW(hcpl, IDS_SEC_SETTINGS, name, ARRAY_SIZE(name));
    lstrcpynW(&name[len], za->szDisplayName, ARRAY_SIZE(name) - len - 1);

    TRACE("new title: %s\n", debugstr_w(name));
    SetWindowTextW(GetDlgItem(sd->hsec, IDC_SEC_GROUP), name);

    update_security_level(sd, lv_index, 0);
    sd->last_lv_index = lv_index;
}