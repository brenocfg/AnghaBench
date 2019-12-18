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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  D3DVALUE ;

/* Variables and functions */
 int D3DFVF_DIFFUSE ; 
 int D3DFVF_NORMAL ; 
 int D3DFVF_POSITION_MASK ; 
 int D3DFVF_RESERVED1 ; 
 int D3DFVF_SPECULAR ; 
#define  D3DFVF_XYZ 134 
#define  D3DFVF_XYZB1 133 
#define  D3DFVF_XYZB2 132 
#define  D3DFVF_XYZB3 131 
#define  D3DFVF_XYZB4 130 
#define  D3DFVF_XYZB5 129 
#define  D3DFVF_XYZRHW 128 
 int /*<<< orphan*/  ERR (char*) ; 
 int GET_TEXCOORD_SIZE_FROM_FVF (int,int) ; 
 int GET_TEXCOUNT_FROM_FVF (int) ; 

DWORD
get_flexible_vertex_size(DWORD d3dvtVertexType)
{
    DWORD size = 0;
    DWORD i;

    if (d3dvtVertexType & D3DFVF_NORMAL) size += 3 * sizeof(D3DVALUE);
    if (d3dvtVertexType & D3DFVF_DIFFUSE) size += sizeof(DWORD);
    if (d3dvtVertexType & D3DFVF_SPECULAR) size += sizeof(DWORD);
    if (d3dvtVertexType & D3DFVF_RESERVED1) size += sizeof(DWORD);
    switch (d3dvtVertexType & D3DFVF_POSITION_MASK)
    {
        case D3DFVF_XYZ:    size += 3 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZRHW: size += 4 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZB1:  size += 4 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZB2:  size += 5 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZB3:  size += 6 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZB4:  size += 7 * sizeof(D3DVALUE); break;
        case D3DFVF_XYZB5:  size += 8 * sizeof(D3DVALUE); break;
        default: ERR("Unexpected position mask\n");
    }
    for (i = 0; i < GET_TEXCOUNT_FROM_FVF(d3dvtVertexType); i++)
    {
        size += GET_TEXCOORD_SIZE_FROM_FVF(d3dvtVertexType, i) * sizeof(D3DVALUE);
    }

    return size;
}