#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dlgw; } ;
struct TYPE_7__ {TYPE_2__ u; scalar_t__ unicode; } ;
typedef  TYPE_3__ pagesetup_data ;
typedef  int /*<<< orphan*/  devnames_name ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  hDevNames; } ;
typedef  int /*<<< orphan*/  DEVNAMES ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int get_devname_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *pagesetup_get_a_devname(const pagesetup_data *data, devnames_name which)
{
    DEVNAMES *dn;
    WCHAR *name;

    dn = GlobalLock(data->u.dlgw->hDevNames);
    if(data->unicode)
        name = strdupW((WCHAR *)dn + get_devname_offset(dn, which));
    else
    {
        int len = MultiByteToWideChar(CP_ACP, 0, (char*)dn + get_devname_offset(dn, which), -1, NULL, 0);
        name = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, 0, (char*)dn + get_devname_offset(dn, which), -1, name, len);
    }
    GlobalUnlock(data->u.dlgw->hDevNames);
    return name;
}