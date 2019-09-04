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
struct TYPE_5__ {int Caps2; int Caps3; int PrimitiveMiscCaps; int RasterCaps; int SrcBlendCaps; int DestBlendCaps; int TextureCaps; int TextureFilterCaps; int CubeTextureFilterCaps; int VolumeTextureFilterCaps; int VertexProcessingCaps; int /*<<< orphan*/  PixelShader1xMaxValue; void* PixelShaderVersion; int /*<<< orphan*/  MaxVertexShaderConst; void* VertexShaderVersion; int /*<<< orphan*/  MaxStreamStride; int /*<<< orphan*/  MaxStreams; int /*<<< orphan*/  MaxVertexIndex; int /*<<< orphan*/  MaxPrimitiveCount; int /*<<< orphan*/  MaxPointSize; int /*<<< orphan*/  MaxVertexBlendMatrixIndex; int /*<<< orphan*/  MaxVertexBlendMatrices; int /*<<< orphan*/  MaxUserClipPlanes; int /*<<< orphan*/  MaxActiveLights; int /*<<< orphan*/  MaxSimultaneousTextures; int /*<<< orphan*/  MaxTextureBlendStages; int /*<<< orphan*/  TextureOpCaps; int /*<<< orphan*/  FVFCaps; int /*<<< orphan*/  StencilCaps; int /*<<< orphan*/  ExtentsAdjust; int /*<<< orphan*/  GuardBandBottom; int /*<<< orphan*/  GuardBandRight; int /*<<< orphan*/  GuardBandTop; int /*<<< orphan*/  GuardBandLeft; int /*<<< orphan*/  MaxVertexW; int /*<<< orphan*/  MaxAnisotropy; int /*<<< orphan*/  MaxTextureAspectRatio; int /*<<< orphan*/  MaxTextureRepeat; int /*<<< orphan*/  MaxVolumeExtent; int /*<<< orphan*/  MaxTextureHeight; int /*<<< orphan*/  MaxTextureWidth; int /*<<< orphan*/  LineCaps; int /*<<< orphan*/  VolumeTextureAddressCaps; int /*<<< orphan*/  TextureAddressCaps; int /*<<< orphan*/  ShadeCaps; int /*<<< orphan*/  AlphaCmpCaps; int /*<<< orphan*/  ZCmpCaps; int /*<<< orphan*/  DevCaps; int /*<<< orphan*/  CursorCaps; int /*<<< orphan*/  Caps; int /*<<< orphan*/  AdapterOrdinal; scalar_t__ DeviceType; } ;
typedef  TYPE_1__ WINED3DCAPS ;
struct TYPE_6__ {int Caps2; int Caps3; int PresentationIntervals; int PrimitiveMiscCaps; int RasterCaps; int SrcBlendCaps; int DestBlendCaps; int TextureCaps; int TextureFilterCaps; int CubeTextureFilterCaps; int VolumeTextureFilterCaps; int VertexProcessingCaps; int /*<<< orphan*/  MaxVertexShaderConst; void* VertexShaderVersion; void* PixelShaderVersion; int /*<<< orphan*/  StencilCaps; int /*<<< orphan*/  MaxPixelShaderValue; int /*<<< orphan*/  MaxStreamStride; int /*<<< orphan*/  MaxStreams; int /*<<< orphan*/  MaxVertexIndex; int /*<<< orphan*/  MaxPrimitiveCount; int /*<<< orphan*/  MaxPointSize; int /*<<< orphan*/  MaxVertexBlendMatrixIndex; int /*<<< orphan*/  MaxVertexBlendMatrices; int /*<<< orphan*/  MaxUserClipPlanes; int /*<<< orphan*/  MaxActiveLights; int /*<<< orphan*/  MaxSimultaneousTextures; int /*<<< orphan*/  MaxTextureBlendStages; int /*<<< orphan*/  TextureOpCaps; int /*<<< orphan*/  FVFCaps; int /*<<< orphan*/  ExtentsAdjust; int /*<<< orphan*/  GuardBandBottom; int /*<<< orphan*/  GuardBandRight; int /*<<< orphan*/  GuardBandTop; int /*<<< orphan*/  GuardBandLeft; int /*<<< orphan*/  MaxVertexW; int /*<<< orphan*/  MaxAnisotropy; int /*<<< orphan*/  MaxTextureAspectRatio; int /*<<< orphan*/  MaxTextureRepeat; int /*<<< orphan*/  MaxVolumeExtent; int /*<<< orphan*/  MaxTextureHeight; int /*<<< orphan*/  MaxTextureWidth; int /*<<< orphan*/  LineCaps; int /*<<< orphan*/  VolumeTextureAddressCaps; int /*<<< orphan*/  TextureAddressCaps; int /*<<< orphan*/  ShadeCaps; int /*<<< orphan*/  AlphaCmpCaps; int /*<<< orphan*/  ZCmpCaps; int /*<<< orphan*/  DevCaps; int /*<<< orphan*/  CursorCaps; int /*<<< orphan*/  Caps; int /*<<< orphan*/  AdapterOrdinal; scalar_t__ DeviceType; } ;
typedef  scalar_t__ D3DDEVTYPE ;
typedef  TYPE_2__ D3DCAPS8 ;

/* Variables and functions */
 int /*<<< orphan*/  D3D8_MAX_VERTEX_SHADER_CONSTANTF ; 
 int D3DCAPS2_CANCALIBRATEGAMMA ; 
 int D3DCAPS2_CANMANAGERESOURCE ; 
 int D3DCAPS2_CANRENDERWINDOWED ; 
 int D3DCAPS2_DYNAMICTEXTURES ; 
 int D3DCAPS2_FULLSCREENGAMMA ; 
 int D3DCAPS2_NO2DDURING3DSCENE ; 
 int D3DCAPS2_RESERVED ; 
 int D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD ; 
 int D3DCAPS3_RESERVED ; 
 int D3DPBLENDCAPS_BOTHINVSRCALPHA ; 
 int D3DPBLENDCAPS_BOTHSRCALPHA ; 
 int D3DPBLENDCAPS_DESTALPHA ; 
 int D3DPBLENDCAPS_DESTCOLOR ; 
 int D3DPBLENDCAPS_INVDESTALPHA ; 
 int D3DPBLENDCAPS_INVDESTCOLOR ; 
 int D3DPBLENDCAPS_INVSRCALPHA ; 
 int D3DPBLENDCAPS_INVSRCCOLOR ; 
 int D3DPBLENDCAPS_ONE ; 
 int D3DPBLENDCAPS_SRCALPHA ; 
 int D3DPBLENDCAPS_SRCALPHASAT ; 
 int D3DPBLENDCAPS_SRCCOLOR ; 
 int D3DPBLENDCAPS_ZERO ; 
 int D3DPMISCCAPS_BLENDOP ; 
 int D3DPMISCCAPS_CLIPPLANESCALEDPOINTS ; 
 int D3DPMISCCAPS_CLIPTLVERTS ; 
 int D3DPMISCCAPS_COLORWRITEENABLE ; 
 int D3DPMISCCAPS_CULLCCW ; 
 int D3DPMISCCAPS_CULLCW ; 
 int D3DPMISCCAPS_CULLNONE ; 
 int D3DPMISCCAPS_LINEPATTERNREP ; 
 int D3DPMISCCAPS_MASKZ ; 
 int D3DPMISCCAPS_NULLREFERENCE ; 
 int D3DPMISCCAPS_TSSARGTEMP ; 
 int D3DPRASTERCAPS_ANISOTROPY ; 
 int D3DPRASTERCAPS_ANTIALIASEDGES ; 
 int D3DPRASTERCAPS_COLORPERSPECTIVE ; 
 int D3DPRASTERCAPS_DITHER ; 
 int D3DPRASTERCAPS_FOGRANGE ; 
 int D3DPRASTERCAPS_FOGTABLE ; 
 int D3DPRASTERCAPS_FOGVERTEX ; 
 int D3DPRASTERCAPS_MIPMAPLODBIAS ; 
 int D3DPRASTERCAPS_PAT ; 
 int D3DPRASTERCAPS_STRETCHBLTMULTISAMPLE ; 
 int D3DPRASTERCAPS_WBUFFER ; 
 int D3DPRASTERCAPS_WFOG ; 
 int D3DPRASTERCAPS_ZBIAS ; 
 int D3DPRASTERCAPS_ZBUFFERLESSHSR ; 
 int D3DPRASTERCAPS_ZFOG ; 
 int D3DPRASTERCAPS_ZTEST ; 
 int D3DPRESENT_INTERVAL_IMMEDIATE ; 
 int D3DPRESENT_INTERVAL_ONE ; 
 void* D3DPS_VERSION (int,int) ; 
 int D3DPTEXTURECAPS_ALPHA ; 
 int D3DPTEXTURECAPS_ALPHAPALETTE ; 
 int D3DPTEXTURECAPS_CUBEMAP ; 
 int D3DPTEXTURECAPS_CUBEMAP_POW2 ; 
 int D3DPTEXTURECAPS_MIPCUBEMAP ; 
 int D3DPTEXTURECAPS_MIPMAP ; 
 int D3DPTEXTURECAPS_MIPVOLUMEMAP ; 
 int D3DPTEXTURECAPS_NONPOW2CONDITIONAL ; 
 int D3DPTEXTURECAPS_PERSPECTIVE ; 
 int D3DPTEXTURECAPS_POW2 ; 
 int D3DPTEXTURECAPS_PROJECTED ; 
 int D3DPTEXTURECAPS_SQUAREONLY ; 
 int D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE ; 
 int D3DPTEXTURECAPS_VOLUMEMAP ; 
 int D3DPTEXTURECAPS_VOLUMEMAP_POW2 ; 
 int D3DPTFILTERCAPS_MAGFAFLATCUBIC ; 
 int D3DPTFILTERCAPS_MAGFANISOTROPIC ; 
 int D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC ; 
 int D3DPTFILTERCAPS_MAGFLINEAR ; 
 int D3DPTFILTERCAPS_MAGFPOINT ; 
 int D3DPTFILTERCAPS_MINFANISOTROPIC ; 
 int D3DPTFILTERCAPS_MINFLINEAR ; 
 int D3DPTFILTERCAPS_MINFPOINT ; 
 int D3DPTFILTERCAPS_MIPFLINEAR ; 
 int D3DPTFILTERCAPS_MIPFPOINT ; 
 void* D3DVS_VERSION (int,int) ; 
 int D3DVTXPCAPS_DIRECTIONALLIGHTS ; 
 int D3DVTXPCAPS_LOCALVIEWER ; 
 int D3DVTXPCAPS_MATERIALSOURCE7 ; 
 int D3DVTXPCAPS_NO_VSDT_UBYTE4 ; 
 int D3DVTXPCAPS_POSITIONALLIGHTS ; 
 int D3DVTXPCAPS_TEXGEN ; 
 int D3DVTXPCAPS_TWEENING ; 
 int /*<<< orphan*/  WINED3DSTENCILCAPS_TWOSIDED ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void d3dcaps_from_wined3dcaps(D3DCAPS8 *caps, const WINED3DCAPS *wined3d_caps)
{
    caps->DeviceType                = (D3DDEVTYPE)wined3d_caps->DeviceType;
    caps->AdapterOrdinal            = wined3d_caps->AdapterOrdinal;
    caps->Caps                      = wined3d_caps->Caps;
    caps->Caps2                     = wined3d_caps->Caps2;
    caps->Caps3                     = wined3d_caps->Caps3;
    caps->PresentationIntervals     = D3DPRESENT_INTERVAL_IMMEDIATE | D3DPRESENT_INTERVAL_ONE;
    caps->CursorCaps                = wined3d_caps->CursorCaps;
    caps->DevCaps                   = wined3d_caps->DevCaps;
    caps->PrimitiveMiscCaps         = wined3d_caps->PrimitiveMiscCaps;
    caps->RasterCaps                = wined3d_caps->RasterCaps;
    caps->ZCmpCaps                  = wined3d_caps->ZCmpCaps;
    caps->SrcBlendCaps              = wined3d_caps->SrcBlendCaps;
    caps->DestBlendCaps             = wined3d_caps->DestBlendCaps;
    caps->AlphaCmpCaps              = wined3d_caps->AlphaCmpCaps;
    caps->ShadeCaps                 = wined3d_caps->ShadeCaps;
    caps->TextureCaps               = wined3d_caps->TextureCaps;
    caps->TextureFilterCaps         = wined3d_caps->TextureFilterCaps;
    caps->CubeTextureFilterCaps     = wined3d_caps->CubeTextureFilterCaps;
    caps->VolumeTextureFilterCaps   = wined3d_caps->VolumeTextureFilterCaps;
    caps->TextureAddressCaps        = wined3d_caps->TextureAddressCaps;
    caps->VolumeTextureAddressCaps  = wined3d_caps->VolumeTextureAddressCaps;
    caps->LineCaps                  = wined3d_caps->LineCaps;
    caps->MaxTextureWidth           = wined3d_caps->MaxTextureWidth;
    caps->MaxTextureHeight          = wined3d_caps->MaxTextureHeight;
    caps->MaxVolumeExtent           = wined3d_caps->MaxVolumeExtent;
    caps->MaxTextureRepeat          = wined3d_caps->MaxTextureRepeat;
    caps->MaxTextureAspectRatio     = wined3d_caps->MaxTextureAspectRatio;
    caps->MaxAnisotropy             = wined3d_caps->MaxAnisotropy;
    caps->MaxVertexW                = wined3d_caps->MaxVertexW;
    caps->GuardBandLeft             = wined3d_caps->GuardBandLeft;
    caps->GuardBandTop              = wined3d_caps->GuardBandTop;
    caps->GuardBandRight            = wined3d_caps->GuardBandRight;
    caps->GuardBandBottom           = wined3d_caps->GuardBandBottom;
    caps->ExtentsAdjust             = wined3d_caps->ExtentsAdjust;
    caps->StencilCaps               = wined3d_caps->StencilCaps;
    caps->FVFCaps                   = wined3d_caps->FVFCaps;
    caps->TextureOpCaps             = wined3d_caps->TextureOpCaps;
    caps->MaxTextureBlendStages     = wined3d_caps->MaxTextureBlendStages;
    caps->MaxSimultaneousTextures   = wined3d_caps->MaxSimultaneousTextures;
    caps->VertexProcessingCaps      = wined3d_caps->VertexProcessingCaps;
    caps->MaxActiveLights           = wined3d_caps->MaxActiveLights;
    caps->MaxUserClipPlanes         = wined3d_caps->MaxUserClipPlanes;
    caps->MaxVertexBlendMatrices    = wined3d_caps->MaxVertexBlendMatrices;
    caps->MaxVertexBlendMatrixIndex = wined3d_caps->MaxVertexBlendMatrixIndex;
    caps->MaxPointSize              = wined3d_caps->MaxPointSize;
    caps->MaxPrimitiveCount         = wined3d_caps->MaxPrimitiveCount;
    caps->MaxVertexIndex            = wined3d_caps->MaxVertexIndex;
    caps->MaxStreams                = wined3d_caps->MaxStreams;
    caps->MaxStreamStride           = wined3d_caps->MaxStreamStride;
    caps->VertexShaderVersion       = wined3d_caps->VertexShaderVersion;
    caps->MaxVertexShaderConst      = wined3d_caps->MaxVertexShaderConst;
    caps->PixelShaderVersion        = wined3d_caps->PixelShaderVersion;
    caps->MaxPixelShaderValue       = wined3d_caps->PixelShader1xMaxValue;

    caps->Caps2 &= D3DCAPS2_CANCALIBRATEGAMMA | D3DCAPS2_CANRENDERWINDOWED
            | D3DCAPS2_CANMANAGERESOURCE | D3DCAPS2_DYNAMICTEXTURES | D3DCAPS2_FULLSCREENGAMMA
            | D3DCAPS2_NO2DDURING3DSCENE | D3DCAPS2_RESERVED;
    caps->Caps3 &= D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD | D3DCAPS3_RESERVED;
    caps->PrimitiveMiscCaps &= D3DPMISCCAPS_MASKZ | D3DPMISCCAPS_LINEPATTERNREP
            | D3DPMISCCAPS_CULLNONE | D3DPMISCCAPS_CULLCW | D3DPMISCCAPS_CULLCCW
            | D3DPMISCCAPS_COLORWRITEENABLE | D3DPMISCCAPS_CLIPPLANESCALEDPOINTS
            | D3DPMISCCAPS_CLIPTLVERTS | D3DPMISCCAPS_TSSARGTEMP | D3DPMISCCAPS_BLENDOP
            | D3DPMISCCAPS_NULLREFERENCE;
    caps->RasterCaps &= D3DPRASTERCAPS_DITHER | D3DPRASTERCAPS_PAT | D3DPRASTERCAPS_ZTEST
            | D3DPRASTERCAPS_FOGVERTEX | D3DPRASTERCAPS_FOGTABLE | D3DPRASTERCAPS_ANTIALIASEDGES
            | D3DPRASTERCAPS_MIPMAPLODBIAS | D3DPRASTERCAPS_ZBIAS | D3DPRASTERCAPS_ZBUFFERLESSHSR
            | D3DPRASTERCAPS_FOGRANGE | D3DPRASTERCAPS_ANISOTROPY | D3DPRASTERCAPS_WBUFFER
            | D3DPRASTERCAPS_WFOG | D3DPRASTERCAPS_ZFOG | D3DPRASTERCAPS_COLORPERSPECTIVE
            | D3DPRASTERCAPS_STRETCHBLTMULTISAMPLE;
    caps->SrcBlendCaps &= D3DPBLENDCAPS_ZERO | D3DPBLENDCAPS_ONE | D3DPBLENDCAPS_SRCCOLOR
            | D3DPBLENDCAPS_INVSRCCOLOR | D3DPBLENDCAPS_SRCALPHA | D3DPBLENDCAPS_INVSRCALPHA
            | D3DPBLENDCAPS_DESTALPHA | D3DPBLENDCAPS_INVDESTALPHA | D3DPBLENDCAPS_DESTCOLOR
            | D3DPBLENDCAPS_INVDESTCOLOR | D3DPBLENDCAPS_SRCALPHASAT | D3DPBLENDCAPS_BOTHSRCALPHA
            | D3DPBLENDCAPS_BOTHINVSRCALPHA;
    caps->DestBlendCaps &= D3DPBLENDCAPS_ZERO | D3DPBLENDCAPS_ONE | D3DPBLENDCAPS_SRCCOLOR
            | D3DPBLENDCAPS_INVSRCCOLOR | D3DPBLENDCAPS_SRCALPHA | D3DPBLENDCAPS_INVSRCALPHA
            | D3DPBLENDCAPS_DESTALPHA | D3DPBLENDCAPS_INVDESTALPHA | D3DPBLENDCAPS_DESTCOLOR
            | D3DPBLENDCAPS_INVDESTCOLOR | D3DPBLENDCAPS_SRCALPHASAT | D3DPBLENDCAPS_BOTHSRCALPHA
            | D3DPBLENDCAPS_BOTHINVSRCALPHA;
    caps->TextureCaps &= D3DPTEXTURECAPS_PERSPECTIVE | D3DPTEXTURECAPS_POW2 | D3DPTEXTURECAPS_ALPHA
            | D3DPTEXTURECAPS_SQUAREONLY | D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE
            | D3DPTEXTURECAPS_ALPHAPALETTE | D3DPTEXTURECAPS_NONPOW2CONDITIONAL
            | D3DPTEXTURECAPS_PROJECTED | D3DPTEXTURECAPS_CUBEMAP | D3DPTEXTURECAPS_VOLUMEMAP
            | D3DPTEXTURECAPS_MIPMAP | D3DPTEXTURECAPS_MIPVOLUMEMAP | D3DPTEXTURECAPS_MIPCUBEMAP
            | D3DPTEXTURECAPS_CUBEMAP_POW2 | D3DPTEXTURECAPS_VOLUMEMAP_POW2;
    caps->TextureFilterCaps &= D3DPTFILTERCAPS_MINFPOINT | D3DPTFILTERCAPS_MINFLINEAR
            | D3DPTFILTERCAPS_MINFANISOTROPIC | D3DPTFILTERCAPS_MIPFPOINT
            | D3DPTFILTERCAPS_MIPFLINEAR | D3DPTFILTERCAPS_MAGFPOINT | D3DPTFILTERCAPS_MAGFLINEAR
            | D3DPTFILTERCAPS_MAGFANISOTROPIC | D3DPTFILTERCAPS_MAGFAFLATCUBIC
            | D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC;
    caps->CubeTextureFilterCaps &= D3DPTFILTERCAPS_MINFPOINT | D3DPTFILTERCAPS_MINFLINEAR
            | D3DPTFILTERCAPS_MINFANISOTROPIC | D3DPTFILTERCAPS_MIPFPOINT
            | D3DPTFILTERCAPS_MIPFLINEAR | D3DPTFILTERCAPS_MAGFPOINT | D3DPTFILTERCAPS_MAGFLINEAR
            | D3DPTFILTERCAPS_MAGFANISOTROPIC | D3DPTFILTERCAPS_MAGFAFLATCUBIC
            | D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC;
    caps->VolumeTextureFilterCaps &= D3DPTFILTERCAPS_MINFPOINT | D3DPTFILTERCAPS_MINFLINEAR
            | D3DPTFILTERCAPS_MINFANISOTROPIC | D3DPTFILTERCAPS_MIPFPOINT
            | D3DPTFILTERCAPS_MIPFLINEAR | D3DPTFILTERCAPS_MAGFPOINT | D3DPTFILTERCAPS_MAGFLINEAR
            | D3DPTFILTERCAPS_MAGFANISOTROPIC | D3DPTFILTERCAPS_MAGFAFLATCUBIC
            | D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC;
    caps->StencilCaps &= ~WINED3DSTENCILCAPS_TWOSIDED;
    caps->VertexProcessingCaps &= D3DVTXPCAPS_TEXGEN | D3DVTXPCAPS_MATERIALSOURCE7
            | D3DVTXPCAPS_DIRECTIONALLIGHTS | D3DVTXPCAPS_POSITIONALLIGHTS | D3DVTXPCAPS_LOCALVIEWER
            | D3DVTXPCAPS_TWEENING | D3DVTXPCAPS_NO_VSDT_UBYTE4;

    /* D3D8 doesn't support SM 2.0 or higher, so clamp to 1.x */
    if (caps->PixelShaderVersion)
        caps->PixelShaderVersion = D3DPS_VERSION(1, 4);
    else
        caps->PixelShaderVersion = D3DPS_VERSION(0, 0);
    if (caps->VertexShaderVersion)
        caps->VertexShaderVersion = D3DVS_VERSION(1, 1);
    else
        caps->VertexShaderVersion = D3DVS_VERSION(0, 0);
    caps->MaxVertexShaderConst = min(D3D8_MAX_VERTEX_SHADER_CONSTANTF, caps->MaxVertexShaderConst);
}