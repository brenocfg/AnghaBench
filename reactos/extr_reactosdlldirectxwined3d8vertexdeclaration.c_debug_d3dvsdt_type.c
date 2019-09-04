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
typedef  int D3DVSDT_TYPE ;

/* Variables and functions */
#define  D3DVSDT_D3DCOLOR 135 
#define  D3DVSDT_FLOAT1 134 
#define  D3DVSDT_FLOAT2 133 
#define  D3DVSDT_FLOAT3 132 
#define  D3DVSDT_FLOAT4 131 
#define  D3DVSDT_SHORT2 130 
#define  D3DVSDT_SHORT4 129 
#define  D3DVSDT_UBYTE4 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const char *debug_d3dvsdt_type(D3DVSDT_TYPE d3dvsdt_type)
{
    switch (d3dvsdt_type)
    {
#define D3DVSDT_TYPE_TO_STR(u) case u: return #u
        D3DVSDT_TYPE_TO_STR(D3DVSDT_FLOAT1);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_FLOAT2);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_FLOAT3);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_FLOAT4);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_D3DCOLOR);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_UBYTE4);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_SHORT2);
        D3DVSDT_TYPE_TO_STR(D3DVSDT_SHORT4);
#undef D3DVSDT_TYPE_TO_STR
        default:
            FIXME("Unrecognized D3DVSDT_TYPE %#x\n", d3dvsdt_type);
            return "unrecognized";
    }
}