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
typedef  int UINT ;
typedef  int D3DPRIMITIVETYPE ;

/* Variables and functions */
#define  D3DPT_LINELIST 133 
#define  D3DPT_LINESTRIP 132 
#define  D3DPT_POINTLIST 131 
#define  D3DPT_TRIANGLEFAN 130 
#define  D3DPT_TRIANGLELIST 129 
#define  D3DPT_TRIANGLESTRIP 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static UINT vertex_count_from_primitive_count(D3DPRIMITIVETYPE primitive_type, UINT primitive_count)
{
    switch (primitive_type)
    {
        case D3DPT_POINTLIST:
            return primitive_count;

        case D3DPT_LINELIST:
            return primitive_count * 2;

        case D3DPT_LINESTRIP:
            return primitive_count + 1;

        case D3DPT_TRIANGLELIST:
            return primitive_count * 3;

        case D3DPT_TRIANGLESTRIP:
        case D3DPT_TRIANGLEFAN:
            return primitive_count + 2;

        default:
            FIXME("Unhandled primitive type %#x.\n", primitive_type);
            return 0;
    }
}