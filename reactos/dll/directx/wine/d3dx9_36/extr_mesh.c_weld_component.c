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
typedef  int /*<<< orphan*/  FLOAT ;
typedef  int D3DDECLTYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  D3DDECLTYPE_D3DCOLOR 145 
#define  D3DDECLTYPE_DEC3N 144 
#define  D3DDECLTYPE_FLOAT1 143 
#define  D3DDECLTYPE_FLOAT16_2 142 
#define  D3DDECLTYPE_FLOAT16_4 141 
#define  D3DDECLTYPE_FLOAT2 140 
#define  D3DDECLTYPE_FLOAT3 139 
#define  D3DDECLTYPE_FLOAT4 138 
#define  D3DDECLTYPE_SHORT2 137 
#define  D3DDECLTYPE_SHORT2N 136 
#define  D3DDECLTYPE_SHORT4 135 
#define  D3DDECLTYPE_SHORT4N 134 
#define  D3DDECLTYPE_UBYTE4 133 
#define  D3DDECLTYPE_UBYTE4N 132 
#define  D3DDECLTYPE_UDEC3 131 
#define  D3DDECLTYPE_UNUSED 130 
#define  D3DDECLTYPE_USHORT2N 129 
#define  D3DDECLTYPE_USHORT4N 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  weld_d3dcolor (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_dec3n (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float1 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float16_2 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float16_4 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float2 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float3 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_float4 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_short2 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_short2n (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_short4 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_short4n (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_ubyte4 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_ubyte4n (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_udec3 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_ushort2n (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weld_ushort4n (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL weld_component(void *to, void *from, D3DDECLTYPE type, FLOAT epsilon)
{
    /* Quiet FIXMEs as this is in a loop with potentially thousand of iterations. */
    BOOL fixme_once_unused = FALSE;
    BOOL fixme_once_unknown = FALSE;

    switch (type)
    {
        case D3DDECLTYPE_FLOAT1:
            return weld_float1(to, from, epsilon);

        case D3DDECLTYPE_FLOAT2:
            return weld_float2(to, from, epsilon);

        case D3DDECLTYPE_FLOAT3:
            return weld_float3(to, from, epsilon);

        case D3DDECLTYPE_FLOAT4:
            return weld_float4(to, from, epsilon);

        case D3DDECLTYPE_D3DCOLOR:
            return weld_d3dcolor(to, from, epsilon);

        case D3DDECLTYPE_UBYTE4:
            return weld_ubyte4(to, from, epsilon);

        case D3DDECLTYPE_SHORT2:
            return weld_short2(to, from, epsilon);

        case D3DDECLTYPE_SHORT4:
            return weld_short4(to, from, epsilon);

        case D3DDECLTYPE_UBYTE4N:
            return weld_ubyte4n(to, from, epsilon);

        case D3DDECLTYPE_SHORT2N:
            return weld_short2n(to, from, epsilon);

        case D3DDECLTYPE_SHORT4N:
            return weld_short4n(to, from, epsilon);

        case D3DDECLTYPE_USHORT2N:
            return weld_ushort2n(to, from, epsilon);

        case D3DDECLTYPE_USHORT4N:
            return weld_ushort4n(to, from, epsilon);

        case D3DDECLTYPE_UDEC3:
            return weld_udec3(to, from, epsilon);

        case D3DDECLTYPE_DEC3N:
            return weld_dec3n(to, from, epsilon);

        case D3DDECLTYPE_FLOAT16_2:
            return weld_float16_2(to, from, epsilon);

        case D3DDECLTYPE_FLOAT16_4:
            return weld_float16_4(to, from, epsilon);

        case D3DDECLTYPE_UNUSED:
            if (!fixme_once_unused++)
                FIXME("D3DDECLTYPE_UNUSED welding not implemented.\n");
            break;

        default:
            if (!fixme_once_unknown++)
                FIXME("Welding of unknown declaration type %d is not implemented.\n", type);
            break;
    }

    return FALSE;
}