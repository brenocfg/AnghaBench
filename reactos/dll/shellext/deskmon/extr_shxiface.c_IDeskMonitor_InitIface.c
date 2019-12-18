#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/ * lpIClassFactoryVtbl; int /*<<< orphan*/ * lpIShellExtInitVtbl; int /*<<< orphan*/ * lpIShellPropSheetExtVtbl; } ;
typedef  TYPE_1__* PDESKMONITOR ;

/* Variables and functions */
 int /*<<< orphan*/  IDeskMonitor_AddRef (TYPE_1__*) ; 
 int /*<<< orphan*/  efvtIClassFactory ; 
 int /*<<< orphan*/  efvtIShellExtInit ; 
 int /*<<< orphan*/  efvtIShellPropSheetExt ; 

VOID
IDeskMonitor_InitIface(PDESKMONITOR This)
{
    This->lpIShellPropSheetExtVtbl = &efvtIShellPropSheetExt;
    This->lpIShellExtInitVtbl = &efvtIShellExtInit;
    This->lpIClassFactoryVtbl = &efvtIClassFactory;

    IDeskMonitor_AddRef(This);
}