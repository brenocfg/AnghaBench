#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {TYPE_3__ IServiceProvider_iface; TYPE_2__ IExternalConnection_iface; TYPE_1__ IWebBrowser2_iface; } ;
typedef  TYPE_4__ InternetExplorer ;

/* Variables and functions */
 int /*<<< orphan*/  ExternalConnectionVtbl ; 
 int /*<<< orphan*/  InternetExplorerVtbl ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 

void InternetExplorer_WebBrowser_Init(InternetExplorer *This)
{
    This->IWebBrowser2_iface.lpVtbl = &InternetExplorerVtbl;
    This->IExternalConnection_iface.lpVtbl = &ExternalConnectionVtbl;
    This->IServiceProvider_iface.lpVtbl = &ServiceProviderVtbl;
}