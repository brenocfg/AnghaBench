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
struct TYPE_3__ {int /*<<< orphan*/  IBindStatusCallback_iface; int /*<<< orphan*/  hres; int /*<<< orphan*/ * obj; scalar_t__ binding; } ;
typedef  TYPE_1__ bsc_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBinding_Abort (scalar_t__) ; 

HRESULT detach_bsc(bsc_t *bsc)
{
    HRESULT hres;

    if(bsc->binding)
        IBinding_Abort(bsc->binding);

    bsc->obj = NULL;
    hres = bsc->hres;
    IBindStatusCallback_Release(&bsc->IBindStatusCallback_iface);

    return hres;
}