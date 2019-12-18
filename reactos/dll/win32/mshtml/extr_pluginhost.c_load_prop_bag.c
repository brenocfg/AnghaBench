#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* element; } ;
struct TYPE_6__ {int /*<<< orphan*/  nselem; } ;
struct TYPE_7__ {TYPE_1__ element; } ;
typedef  TYPE_3__ PluginHost ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  IPersistPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPersistPropertyBag_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistPropertyBag_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_load_safety (TYPE_3__*) ; 
 int /*<<< orphan*/  create_param_prop_bag (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void load_prop_bag(PluginHost *host, IPersistPropertyBag *persist_prop_bag)
{
    IPropertyBag *prop_bag;
    HRESULT hres;

    hres = create_param_prop_bag(host->element->element.nselem, &prop_bag);
    if(FAILED(hres))
        return;

    if(prop_bag && !check_load_safety(host)) {
        IPropertyBag_Release(prop_bag);
        prop_bag = NULL;
    }

    if(prop_bag) {
        hres = IPersistPropertyBag_Load(persist_prop_bag, prop_bag, NULL);
        IPropertyBag_Release(prop_bag);
        if(FAILED(hres))
            WARN("Load failed: %08x\n", hres);
    }else {
        hres = IPersistPropertyBag_InitNew(persist_prop_bag);
        if(FAILED(hres))
            WARN("InitNew failed: %08x\n", hres);
    }
}