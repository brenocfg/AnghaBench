#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_5__ {TYPE_1__ filter; } ;
struct TYPE_6__ {TYPE_2__ tf; int /*<<< orphan*/ * pBihOut; int /*<<< orphan*/ * pBihIn; int /*<<< orphan*/ * hvid; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ AVIDecImpl ;

/* Variables and functions */
 int /*<<< orphan*/  AVIDec_FuncsTable ; 
 int /*<<< orphan*/  AVIDec_Vtbl ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_AVIDec ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TransformFilter_Construct (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT AVIDec_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    HRESULT hr;
    AVIDecImpl * This;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    hr = TransformFilter_Construct(&AVIDec_Vtbl, sizeof(AVIDecImpl), &CLSID_AVIDec, &AVIDec_FuncsTable, (IBaseFilter**)&This);

    if (FAILED(hr))
        return hr;

    This->hvid = NULL;
    This->pBihIn = NULL;
    This->pBihOut = NULL;

    *ppv = &This->tf.filter.IBaseFilter_iface;

    return hr;
}