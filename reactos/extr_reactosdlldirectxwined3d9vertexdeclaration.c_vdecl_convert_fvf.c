#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int component_count; unsigned int component_size; } ;
struct TYPE_6__ {size_t Type; int UsageIndex; unsigned int Offset; int /*<<< orphan*/  Method; scalar_t__ Stream; void* Usage; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ D3DVERTEXELEMENT9 ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DDECLMETHOD_DEFAULT ; 
 void* D3DDECLTYPE_D3DCOLOR ; 
 void* D3DDECLTYPE_FLOAT1 ; 
 void* D3DDECLTYPE_FLOAT2 ; 
 void* D3DDECLTYPE_FLOAT3 ; 
 void* D3DDECLTYPE_FLOAT4 ; 
 size_t D3DDECLTYPE_UBYTE4 ; 
 void* D3DDECLUSAGE_BLENDINDICES ; 
 void* D3DDECLUSAGE_BLENDWEIGHT ; 
 void* D3DDECLUSAGE_COLOR ; 
 void* D3DDECLUSAGE_NORMAL ; 
 void* D3DDECLUSAGE_POSITION ; 
 void* D3DDECLUSAGE_POSITIONT ; 
 void* D3DDECLUSAGE_PSIZE ; 
 void* D3DDECLUSAGE_TEXCOORD ; 
 TYPE_1__ D3DDECL_END () ; 
 int /*<<< orphan*/  D3DERR_OUTOFVIDEOMEMORY ; 
 int D3DFVF_DIFFUSE ; 
 int D3DFVF_LASTBETA_D3DCOLOR ; 
 int D3DFVF_LASTBETA_UBYTE4 ; 
 int D3DFVF_NORMAL ; 
 int D3DFVF_POSITION_MASK ; 
 int D3DFVF_PSIZE ; 
 int D3DFVF_SPECULAR ; 
 int D3DFVF_TEXCOUNT_MASK ; 
 int D3DFVF_TEXCOUNT_SHIFT ; 
#define  D3DFVF_TEXTUREFORMAT1 131 
#define  D3DFVF_TEXTUREFORMAT2 130 
#define  D3DFVF_TEXTUREFORMAT3 129 
#define  D3DFVF_TEXTUREFORMAT4 128 
 int D3DFVF_XYZB1 ; 
 int D3DFVF_XYZB2 ; 
 int D3DFVF_XYZB5 ; 
 int D3DFVF_XYZRHW ; 
 int D3DFVF_XYZW ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 TYPE_4__* d3d_dtype_lookup ; 
 TYPE_1__* heap_alloc (unsigned int) ; 

HRESULT vdecl_convert_fvf(
    DWORD fvf,
    D3DVERTEXELEMENT9** ppVertexElements) {

    unsigned int idx, idx2;
    unsigned int offset;
    BOOL has_pos = (fvf & D3DFVF_POSITION_MASK) != 0;
    BOOL has_blend = (fvf & D3DFVF_XYZB5) > D3DFVF_XYZRHW;
    BOOL has_blend_idx = has_blend &&
       (((fvf & D3DFVF_XYZB5) == D3DFVF_XYZB5) ||
        (fvf & D3DFVF_LASTBETA_D3DCOLOR) ||
        (fvf & D3DFVF_LASTBETA_UBYTE4));
    BOOL has_normal = (fvf & D3DFVF_NORMAL) != 0;
    BOOL has_psize = (fvf & D3DFVF_PSIZE) != 0;

    BOOL has_diffuse = (fvf & D3DFVF_DIFFUSE) != 0;
    BOOL has_specular = (fvf & D3DFVF_SPECULAR) !=0;

    DWORD num_textures = (fvf & D3DFVF_TEXCOUNT_MASK) >> D3DFVF_TEXCOUNT_SHIFT;
    DWORD texcoords = (fvf & 0xFFFF0000) >> 16;

    D3DVERTEXELEMENT9 end_element = D3DDECL_END();
    D3DVERTEXELEMENT9 *elements = NULL;

    unsigned int size;
    DWORD num_blends = 1 + (((fvf & D3DFVF_XYZB5) - D3DFVF_XYZB1) >> 1);
    if (has_blend_idx) num_blends--;

    /* Compute declaration size */
    size = has_pos + (has_blend && num_blends > 0) + has_blend_idx + has_normal +
           has_psize + has_diffuse + has_specular + num_textures + 1;

    /* convert the declaration */
    if (!(elements = heap_alloc(size * sizeof(*elements))))
        return D3DERR_OUTOFVIDEOMEMORY;

    elements[size-1] = end_element;
    idx = 0;
    if (has_pos) {
        if (!has_blend && (fvf & D3DFVF_XYZRHW)) {
            elements[idx].Type = D3DDECLTYPE_FLOAT4;
            elements[idx].Usage = D3DDECLUSAGE_POSITIONT;
        }
        else if (!has_blend && (fvf & D3DFVF_XYZW) == D3DFVF_XYZW) {
            elements[idx].Type = D3DDECLTYPE_FLOAT4;
            elements[idx].Usage = D3DDECLUSAGE_POSITION;
        }
        else {
            elements[idx].Type = D3DDECLTYPE_FLOAT3;
            elements[idx].Usage = D3DDECLUSAGE_POSITION;
        }
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_blend && (num_blends > 0)) {
        if (((fvf & D3DFVF_XYZB5) == D3DFVF_XYZB2) && (fvf & D3DFVF_LASTBETA_D3DCOLOR))
            elements[idx].Type = D3DDECLTYPE_D3DCOLOR;
        else {
            switch(num_blends) {
                case 1: elements[idx].Type = D3DDECLTYPE_FLOAT1; break;
                case 2: elements[idx].Type = D3DDECLTYPE_FLOAT2; break;
                case 3: elements[idx].Type = D3DDECLTYPE_FLOAT3; break;
                case 4: elements[idx].Type = D3DDECLTYPE_FLOAT4; break;
                default:
                    ERR("Unexpected amount of blend values: %u\n", num_blends);
            }
        }
        elements[idx].Usage = D3DDECLUSAGE_BLENDWEIGHT;
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_blend_idx) {
        if (fvf & D3DFVF_LASTBETA_UBYTE4 ||
            (((fvf & D3DFVF_XYZB5) == D3DFVF_XYZB2) && (fvf & D3DFVF_LASTBETA_D3DCOLOR)))
            elements[idx].Type = D3DDECLTYPE_UBYTE4;
        else if (fvf & D3DFVF_LASTBETA_D3DCOLOR)
            elements[idx].Type = D3DDECLTYPE_D3DCOLOR;
        else
            elements[idx].Type = D3DDECLTYPE_FLOAT1;
        elements[idx].Usage = D3DDECLUSAGE_BLENDINDICES;
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_normal) {
        elements[idx].Type = D3DDECLTYPE_FLOAT3;
        elements[idx].Usage = D3DDECLUSAGE_NORMAL;
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_psize) {
        elements[idx].Type = D3DDECLTYPE_FLOAT1;
        elements[idx].Usage = D3DDECLUSAGE_PSIZE;
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_diffuse) {
        elements[idx].Type = D3DDECLTYPE_D3DCOLOR;
        elements[idx].Usage = D3DDECLUSAGE_COLOR;
        elements[idx].UsageIndex = 0;
        idx++;
    }
    if (has_specular) {
        elements[idx].Type = D3DDECLTYPE_D3DCOLOR;
        elements[idx].Usage = D3DDECLUSAGE_COLOR;
        elements[idx].UsageIndex = 1;
        idx++;
    }
    for (idx2 = 0; idx2 < num_textures; idx2++) {
        unsigned int numcoords = (texcoords >> (idx2*2)) & 0x03;
        switch (numcoords) {
            case D3DFVF_TEXTUREFORMAT1:
                elements[idx].Type = D3DDECLTYPE_FLOAT1;
                break;
            case D3DFVF_TEXTUREFORMAT2:
                elements[idx].Type = D3DDECLTYPE_FLOAT2;
                break;
            case D3DFVF_TEXTUREFORMAT3:
                elements[idx].Type = D3DDECLTYPE_FLOAT3;
                break;
            case D3DFVF_TEXTUREFORMAT4:
                elements[idx].Type = D3DDECLTYPE_FLOAT4;
                break;
        }
        elements[idx].Usage = D3DDECLUSAGE_TEXCOORD;
        elements[idx].UsageIndex = idx2;
        idx++;
    }

    /* Now compute offsets, and initialize the rest of the fields */
    for (idx = 0, offset = 0; idx < size-1; idx++) {
        elements[idx].Stream = 0;
        elements[idx].Method = D3DDECLMETHOD_DEFAULT;
        elements[idx].Offset = offset;
        offset += d3d_dtype_lookup[elements[idx].Type].component_count
                * d3d_dtype_lookup[elements[idx].Type].component_size;
    }

    *ppVertexElements = elements;
    return D3D_OK;
}