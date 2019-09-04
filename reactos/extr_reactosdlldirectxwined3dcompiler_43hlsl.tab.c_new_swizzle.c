#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct source_location {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_type; struct source_location loc; int /*<<< orphan*/  type; } ;
struct hlsl_ir_swizzle {int /*<<< orphan*/  swizzle; struct hlsl_ir_node* val; TYPE_2__ node; } ;
struct hlsl_ir_node {TYPE_1__* data_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  base_type; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HLSL_CLASS_VECTOR ; 
 int /*<<< orphan*/  HLSL_IR_SWIZZLE ; 
 struct hlsl_ir_swizzle* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  new_hlsl_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static struct hlsl_ir_swizzle *new_swizzle(DWORD s, unsigned int components,
        struct hlsl_ir_node *val, struct source_location *loc)
{
    struct hlsl_ir_swizzle *swizzle = d3dcompiler_alloc(sizeof(*swizzle));

    if (!swizzle)
        return NULL;
    swizzle->node.type = HLSL_IR_SWIZZLE;
    swizzle->node.loc = *loc;
    swizzle->node.data_type = new_hlsl_type(NULL, HLSL_CLASS_VECTOR, val->data_type->base_type, components, 1);
    swizzle->val = val;
    swizzle->swizzle = s;
    return swizzle;
}