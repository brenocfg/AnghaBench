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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int /*<<< orphan*/ * pFilter; } ;
typedef  scalar_t__ (* SendPinFunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  TYPE_1__ PIN_INFO ;
typedef  scalar_t__ PIN_DIRECTION ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IEnumPins ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IBaseFilter_EnumPins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumPins_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumPins_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumPins_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_ConnectedTo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPin_QueryDirection (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IPin_QueryInternalConnections (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IPin_QueryPinInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VFW_E_ENUM_OUT_OF_SYNC ; 
 scalar_t__ updatehres (scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT SendFurther( IPin *from, SendPinFunc fnMiddle, LPVOID arg, SendPinFunc fnEnd )
{
    PIN_INFO pin_info;
    ULONG amount = 0;
    HRESULT hr = S_OK;
    HRESULT hr_return = S_OK;
    IEnumPins *enumpins = NULL;
    BOOL foundend = TRUE;
    PIN_DIRECTION from_dir;

    IPin_QueryDirection( from, &from_dir );

    hr = IPin_QueryInternalConnections( from, NULL, &amount );
    if (hr != E_NOTIMPL && amount)
        FIXME("Use QueryInternalConnections!\n");

    pin_info.pFilter = NULL;
    hr = IPin_QueryPinInfo( from, &pin_info );
    if (FAILED(hr))
        goto out;

    hr = IBaseFilter_EnumPins( pin_info.pFilter, &enumpins );
    if (FAILED(hr))
        goto out;

    hr = IEnumPins_Reset( enumpins );
    while (hr == S_OK) {
        IPin *pin = NULL;
        hr = IEnumPins_Next( enumpins, 1, &pin, NULL );
        if (hr == VFW_E_ENUM_OUT_OF_SYNC)
        {
            hr = IEnumPins_Reset( enumpins );
            continue;
        }
        if (pin)
        {
            PIN_DIRECTION dir;

            IPin_QueryDirection( pin, &dir );
            if (dir != from_dir)
            {
                IPin *connected = NULL;

                foundend = FALSE;
                IPin_ConnectedTo( pin, &connected );
                if (connected)
                {
                    HRESULT hr_local;

                    hr_local = fnMiddle( connected, arg );
                    hr_return = updatehres( hr_return, hr_local );
                    IPin_Release(connected);
                }
            }
            IPin_Release( pin );
        }
        else
        {
            hr = S_OK;
            break;
        }
    }

    if (!foundend)
        hr = hr_return;
    else if (fnEnd) {
        HRESULT hr_local;

        hr_local = fnEnd( from, arg );
        hr_return = updatehres( hr_return, hr_local );
    }

out:
    if (enumpins)
        IEnumPins_Release( enumpins );
    if (pin_info.pFilter)
        IBaseFilter_Release( pin_info.pFilter );
    return hr;
}