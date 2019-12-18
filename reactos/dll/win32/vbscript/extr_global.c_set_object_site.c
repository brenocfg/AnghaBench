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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IObjectWithSite ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IObjectWithSite ; 
 int /*<<< orphan*/  IObjectWithSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IObjectWithSite_SetSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * create_ax_site (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT set_object_site(script_ctx_t *ctx, IUnknown *obj)
{
    IObjectWithSite *obj_site;
    IUnknown *ax_site;
    HRESULT hres;

    hres = IUnknown_QueryInterface(obj, &IID_IObjectWithSite, (void**)&obj_site);
    if(FAILED(hres))
        return S_OK;

    ax_site = create_ax_site(ctx);
    if(ax_site) {
        hres = IObjectWithSite_SetSite(obj_site, ax_site);
        IUnknown_Release(ax_site);
    }
    else
        hres = E_OUTOFMEMORY;
    IObjectWithSite_Release(obj_site);
    return hres;
}