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
struct TYPE_3__ {int /*<<< orphan*/ * serv_prov; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ BindStatusCallback ;

/* Variables and functions */
 int /*<<< orphan*/  IBindStatusCallback_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IBindStatusCallback_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static void set_callback(BindStatusCallback *This, IBindStatusCallback *bsc)
{
    IServiceProvider *serv_prov;
    HRESULT hres;

    if(This->callback)
        IBindStatusCallback_Release(This->callback);
    if(This->serv_prov)
        IServiceProvider_Release(This->serv_prov);

    IBindStatusCallback_AddRef(bsc);
    This->callback = bsc;

    hres = IBindStatusCallback_QueryInterface(bsc, &IID_IServiceProvider, (void**)&serv_prov);
    This->serv_prov = hres == S_OK ? serv_prov : NULL;
}