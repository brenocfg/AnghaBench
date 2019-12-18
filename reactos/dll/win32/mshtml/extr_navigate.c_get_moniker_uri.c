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
typedef  int /*<<< orphan*/  IUriContainer ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IUriContainer ; 
 int /*<<< orphan*/  IMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUriContainer_GetIUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUriContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IUri *get_moniker_uri(IMoniker *mon)
{
    IUriContainer *uri_container;
    IUri *ret = NULL;
    HRESULT hres;

    hres = IMoniker_QueryInterface(mon, &IID_IUriContainer, (void**)&uri_container);
    if(SUCCEEDED(hres)) {
        hres = IUriContainer_GetIUri(uri_container, &ret);
        IUriContainer_Release(uri_container);
        if(FAILED(hres))
            return NULL;
    }else {
        FIXME("No IUriContainer\n");
    }

    return ret;
}