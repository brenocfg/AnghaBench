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
struct TYPE_3__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DownloadBSC ;

/* Variables and functions */
 int /*<<< orphan*/  DownloadBSC_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT create_default_callback(IBindStatusCallback **ret)
{
    DownloadBSC *callback;
    HRESULT hres;

    hres = DownloadBSC_Create(NULL, NULL, &callback);
    if(FAILED(hres))
        return hres;

    hres = wrap_callback(&callback->IBindStatusCallback_iface, ret);
    IBindStatusCallback_Release(&callback->IBindStatusCallback_iface);
    return hres;
}