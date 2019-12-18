#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hlsl_type {int dimy; int dimx; int base_type; } ;
struct TYPE_5__ {int /*<<< orphan*/ * b; int /*<<< orphan*/ * u; int /*<<< orphan*/ * i; int /*<<< orphan*/ * d; scalar_t__* f; } ;
struct TYPE_6__ {TYPE_2__ value; } ;
struct TYPE_4__ {struct hlsl_type* data_type; } ;
struct hlsl_ir_constant {TYPE_3__ v; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  HLSL_TYPE_BOOL 132 
#define  HLSL_TYPE_DOUBLE 131 
#define  HLSL_TYPE_FLOAT 130 
#define  HLSL_TYPE_INT 129 
#define  HLSL_TYPE_UINT 128 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debug_base_type (struct hlsl_type*) ; 

__attribute__((used)) static void debug_dump_ir_constant(const struct hlsl_ir_constant *constant)
{
    struct hlsl_type *type = constant->node.data_type;
    unsigned int x, y;

    if (type->dimy != 1)
        TRACE("{");
    for (y = 0; y < type->dimy; ++y)
    {
        if (type->dimx != 1)
            TRACE("{");
        for (x = 0; x < type->dimx; ++x)
        {
            switch (type->base_type)
            {
                case HLSL_TYPE_FLOAT:
                    TRACE("%g ", (double)constant->v.value.f[y * type->dimx + x]);
                    break;
                case HLSL_TYPE_DOUBLE:
                    TRACE("%g ", constant->v.value.d[y * type->dimx + x]);
                    break;
                case HLSL_TYPE_INT:
                    TRACE("%d ", constant->v.value.i[y * type->dimx + x]);
                    break;
                case HLSL_TYPE_UINT:
                    TRACE("%u ", constant->v.value.u[y * type->dimx + x]);
                    break;
                case HLSL_TYPE_BOOL:
                    TRACE("%s ", constant->v.value.b[y * type->dimx + x] == FALSE ? "false" : "true");
                    break;
                default:
                    TRACE("Constants of type %s not supported\n", debug_base_type(type));
            }
        }
        if (type->dimx != 1)
            TRACE("}");
    }
    if (type->dimy != 1)
        TRACE("}");
}