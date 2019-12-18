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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_GetObjectParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IBindStatusCallback ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bscb_holderW ; 
 int /*<<< orphan*/  create_default_callback (int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT get_callback(IBindCtx *pbc, IBindStatusCallback **callback)
{
    IUnknown *unk;
    HRESULT hres;

    hres = IBindCtx_GetObjectParam(pbc, bscb_holderW, &unk);
    if(FAILED(hres))
        return create_default_callback(callback);

    hres = IUnknown_QueryInterface(unk, &IID_IBindStatusCallback, (void**)callback);
    IUnknown_Release(unk);
    return hres;
}