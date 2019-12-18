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
struct TYPE_5__ {int /*<<< orphan*/  plugin_unk; } ;
struct TYPE_4__ {TYPE_2__* plugin_host; } ;
typedef  int /*<<< orphan*/  IOleControl ;
typedef  TYPE_1__ HTMLPluginContainer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IOleControl ; 
 int /*<<< orphan*/  IOleControl_OnAmbientPropertyChange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleControl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notif_enabled (TYPE_2__*) ; 

void notif_container_change(HTMLPluginContainer *plugin_container, DISPID dispid)
{
    IOleControl *ole_control;
    HRESULT hres;

    if(!plugin_container->plugin_host || !plugin_container->plugin_host->plugin_unk)
        return;

    notif_enabled(plugin_container->plugin_host);

    hres = IUnknown_QueryInterface(plugin_container->plugin_host->plugin_unk, &IID_IOleControl, (void**)&ole_control);
    if(SUCCEEDED(hres)) {
        IOleControl_OnAmbientPropertyChange(ole_control, dispid);
        IOleControl_Release(ole_control);
    }
}