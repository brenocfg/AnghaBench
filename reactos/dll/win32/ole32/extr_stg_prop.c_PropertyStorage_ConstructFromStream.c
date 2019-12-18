#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IPropertyStorage_iface; } ;
typedef  int /*<<< orphan*/  REFFMTID ;
typedef  TYPE_1__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPropertyStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IPropertyStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropertyStorage_BaseConstruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  PropertyStorage_ReadFromStream (TYPE_1__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT PropertyStorage_ConstructFromStream(IStream *stm,
 REFFMTID rfmtid, DWORD grfMode, IPropertyStorage** pps)
{
    PropertyStorage_impl *ps;
    HRESULT hr;

    assert(pps);
    hr = PropertyStorage_BaseConstruct(stm, rfmtid, grfMode, &ps);
    if (SUCCEEDED(hr))
    {
        hr = PropertyStorage_ReadFromStream(ps);
        if (SUCCEEDED(hr))
        {
            *pps = &ps->IPropertyStorage_iface;
            TRACE("PropertyStorage %p constructed\n", ps);
            hr = S_OK;
        }
        else IPropertyStorage_Release( &ps->IPropertyStorage_iface );
    }
    return hr;
}