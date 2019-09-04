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
typedef  int /*<<< orphan*/  LPD3D9_DRIVERCAPS ;
typedef  int D3DFORMAT ;

/* Variables and functions */
#define  D3DFMT_D15S1 132 
#define  D3DFMT_D16 131 
 int D3DFMT_D16_LOCKABLE ; 
#define  D3DFMT_D24S8 130 
#define  D3DFMT_D24X4S4 129 
#define  D3DFMT_D24X8 128 
 int /*<<< orphan*/  IsSupportedFormatOp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static D3DFORMAT GetStencilFormat(LPD3D9_DRIVERCAPS pDriverCaps, D3DFORMAT CheckFormat)
{
    switch (CheckFormat)
    {
    case D3DFMT_D15S1:
    case D3DFMT_D24S8:
    case D3DFMT_D24X8:
    case D3DFMT_D24X4S4:
        if (IsSupportedFormatOp(pDriverCaps, CheckFormat - 1, 0))
            return CheckFormat - 1;
        break;

    case D3DFMT_D16:
        if (IsSupportedFormatOp(pDriverCaps, CheckFormat, 0))
            return CheckFormat;
        else
            return D3DFMT_D16_LOCKABLE;

    default:
        /* StencilFormat same as CheckFormat */
        break;
    }

    return CheckFormat;
}