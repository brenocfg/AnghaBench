#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Caps; int Caps2; int Caps3; int DevCaps; int PresentationIntervals; int PrimitiveMiscCaps; int VertexProcessingCaps; float MaxPointSize; int /*<<< orphan*/  RasterCaps; } ;
typedef  TYPE_1__ D3DCAPS9 ;

/* Variables and functions */
 int D3D9_CAPS1 ; 
 int D3D9_CAPS3 ; 
 int D3D9_DEVCAPS ; 
 int D3D9_PRE_XP_CAPS2 ; 
 int D3D9_XP_OR_LATER_CAPS2 ; 
 int D3DCAPS2_PRESENT_INTERVAL_IMMEDIATE ; 
 int D3DCAPS2_PRESENT_INTERVAL_SEVERAL ; 
 int D3DPMISCCAPS_FOGINFVF ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_FOGVERTEX ; 
 int D3DPRESENT_INTERVAL_FOUR ; 
 int D3DPRESENT_INTERVAL_IMMEDIATE ; 
 int D3DPRESENT_INTERVAL_ONE ; 
 int D3DPRESENT_INTERVAL_THREE ; 
 int D3DPRESENT_INTERVAL_TWO ; 
 int D3DVTXPCAPS_FOGVERTEX ; 
 scalar_t__ IsWindowsXPorLaterCompatible () ; 

__attribute__((used)) static void CopyDriverCaps(const D3DCAPS9* pSrcCaps, D3DCAPS9* pDstCaps)
{
    *pDstCaps = *pSrcCaps;

    pDstCaps->Caps = pSrcCaps->Caps & D3D9_CAPS1;

    /* TODO: Fit in D3DCAPS2_CANCALIBRATEGAMMA somewhere here */
    if (IsWindowsXPorLaterCompatible())
        pDstCaps->Caps2 = pSrcCaps->Caps2 & D3D9_XP_OR_LATER_CAPS2;
    else
        pDstCaps->Caps2 = pSrcCaps->Caps2 & D3D9_PRE_XP_CAPS2;

    pDstCaps->Caps3 = pSrcCaps->Caps3 & D3D9_CAPS3;
    pDstCaps->DevCaps = pSrcCaps->DevCaps & D3D9_DEVCAPS;

    pDstCaps->PresentationIntervals = D3DPRESENT_INTERVAL_ONE;
    if (pSrcCaps->Caps2 & D3DCAPS2_PRESENT_INTERVAL_SEVERAL)
        pDstCaps->PresentationIntervals |= (D3DPRESENT_INTERVAL_TWO | D3DPRESENT_INTERVAL_THREE | D3DPRESENT_INTERVAL_FOUR);
    if (pSrcCaps->Caps2 & D3DCAPS2_PRESENT_INTERVAL_IMMEDIATE)
        pDstCaps->PresentationIntervals |= D3DPRESENT_INTERVAL_IMMEDIATE;

    pDstCaps->PrimitiveMiscCaps = pSrcCaps->PrimitiveMiscCaps & ~D3DPMISCCAPS_FOGINFVF;

    if (pSrcCaps->VertexProcessingCaps & D3DVTXPCAPS_FOGVERTEX)
    {
        pDstCaps->RasterCaps |= D3DPRASTERCAPS_FOGVERTEX;
        pDstCaps->VertexProcessingCaps &= ~D3DVTXPCAPS_FOGVERTEX;
    }

    if (pSrcCaps->MaxPointSize < 0.0f)
        pDstCaps->MaxPointSize = 1.0f;
}