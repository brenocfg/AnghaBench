#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ DevCaps2; } ;
struct TYPE_6__ {TYPE_1__ DriverCaps9; } ;
typedef  TYPE_2__* LPD3D9_DRIVERCAPS ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_NOTAVAILABLE ; 
#define  D3DFMT_A1R5G5B5 133 
#define  D3DFMT_A2R10G10B10 132 
#define  D3DFMT_A8R8G8B8 131 
#define  D3DFMT_R5G6B5 130 
#define  D3DFMT_X1R5G5B5 129 
#define  D3DFMT_X8R8G8B8 128 
 int /*<<< orphan*/  D3DFORMAT_MEMBEROFGROUP_ARGB ; 
 int /*<<< orphan*/  D3DFORMAT_OP_CONVERT_TO_ARGB ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ IsFourCCFormat (scalar_t__) ; 
 scalar_t__ IsSupportedFormatOp (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RemoveAlphaChannel (scalar_t__) ; 

HRESULT CheckDeviceFormatConversion(LPD3D9_DRIVERCAPS pDriverCaps, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
    D3DFORMAT NonAlphaSourceFormat;
    D3DFORMAT NonAlphaTargetFormat;

    NonAlphaSourceFormat = RemoveAlphaChannel(SourceFormat);
    NonAlphaTargetFormat = RemoveAlphaChannel(TargetFormat);

    if (NonAlphaSourceFormat == NonAlphaTargetFormat)
    {
        return D3D_OK;
    }

    if (FALSE == IsFourCCFormat(SourceFormat))
    {
        switch (SourceFormat)
        {
        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        case D3DFMT_R5G6B5:
        case D3DFMT_X1R5G5B5:
        case D3DFMT_A1R5G5B5:
        case D3DFMT_A2R10G10B10:
            /* Do nothing, valid SourceFormat */
            break;

        default:
            return D3DERR_NOTAVAILABLE;
        }
    }
    else if (pDriverCaps->DriverCaps9.DevCaps2 == 0)
    {
        return D3D_OK;
    }

    if (FALSE == IsSupportedFormatOp(pDriverCaps, SourceFormat, D3DFORMAT_OP_CONVERT_TO_ARGB) ||
        FALSE == IsSupportedFormatOp(pDriverCaps, TargetFormat, D3DFORMAT_MEMBEROFGROUP_ARGB))
    {
        return D3DERR_NOTAVAILABLE;
    }

    return D3D_OK;
}