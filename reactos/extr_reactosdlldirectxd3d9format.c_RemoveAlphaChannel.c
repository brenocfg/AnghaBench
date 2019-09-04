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
typedef  int D3DFORMAT ;

/* Variables and functions */
#define  D3DFMT_A1R5G5B5 131 
#define  D3DFMT_A4R4G4B4 130 
#define  D3DFMT_A8B8G8R8 129 
#define  D3DFMT_A8R8G8B8 128 
 int D3DFMT_X1R5G5B5 ; 
 int D3DFMT_X4R4G4B4 ; 
 int D3DFMT_X8B8G8R8 ; 
 int D3DFMT_X8R8G8B8 ; 

__attribute__((used)) static D3DFORMAT RemoveAlphaChannel(D3DFORMAT CheckFormat)
{
    switch (CheckFormat)
    {
    case D3DFMT_A8R8G8B8:
        return D3DFMT_X8R8G8B8;

    case D3DFMT_A1R5G5B5:
        return D3DFMT_X1R5G5B5;

    case D3DFMT_A4R4G4B4:
        return D3DFMT_X4R4G4B4;

    case D3DFMT_A8B8G8R8:
        return D3DFMT_X8B8G8R8;

    default:
        /* CheckFormat has not relevant alpha channel */
        break;
    }

    return CheckFormat;
}