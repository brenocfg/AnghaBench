#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pidlAbsCurrent; } ;
struct TYPE_16__ {TYPE_3__ ShellInfos; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int ref; TYPE_5__ IShellBrowser_iface; TYPE_2__ IServiceProvider_iface; TYPE_1__ ICommDlgBrowser_iface; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_4__ IShellBrowserImpl ;
typedef  TYPE_5__ IShellBrowser ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_6__ FileOpenDlgInfos ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  IShellBrowserImpl_ICommDlgBrowser_Vtbl ; 
 int /*<<< orphan*/  IShellBrowserImpl_IServiceProvider_Vtbl ; 
 int /*<<< orphan*/  IShellBrowserImpl_Vtbl ; 
 int /*<<< orphan*/  SHGetSpecialFolderLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 TYPE_6__* get_filedlg_infoptr (int /*<<< orphan*/ ) ; 
 TYPE_4__* heap_alloc (int) ; 

IShellBrowser * IShellBrowserImpl_Construct(HWND hwndOwner)
{
    FileOpenDlgInfos *fodInfos = get_filedlg_infoptr(hwndOwner);
    IShellBrowserImpl *sb;

    sb = heap_alloc(sizeof(*sb));

    /* Initialisation of the member variables */
    sb->ref=1;
    sb->hwndOwner = hwndOwner;

    /* Initialisation of the vTables */
    sb->IShellBrowser_iface.lpVtbl = &IShellBrowserImpl_Vtbl;
    sb->ICommDlgBrowser_iface.lpVtbl = &IShellBrowserImpl_ICommDlgBrowser_Vtbl;
    sb->IServiceProvider_iface.lpVtbl = &IShellBrowserImpl_IServiceProvider_Vtbl;
    SHGetSpecialFolderLocation(hwndOwner, CSIDL_DESKTOP,
                               &fodInfos->ShellInfos.pidlAbsCurrent);

    TRACE("%p\n", sb);

    return &sb->IShellBrowser_iface;
}