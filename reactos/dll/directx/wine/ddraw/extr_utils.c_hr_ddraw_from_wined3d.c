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
typedef  int HRESULT ;

/* Variables and functions */
 int DDERR_INVALIDPARAMS ; 
#define  WINED3DERR_INVALIDCALL 128 

HRESULT
hr_ddraw_from_wined3d(HRESULT hr)
{
    switch(hr)
    {
        case WINED3DERR_INVALIDCALL: return DDERR_INVALIDPARAMS;
        default: return hr;
    }
}