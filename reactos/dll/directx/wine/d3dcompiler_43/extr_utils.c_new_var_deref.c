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
struct hlsl_ir_var {int /*<<< orphan*/  data_type; } ;
struct TYPE_4__ {struct hlsl_ir_var* var; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_type; int /*<<< orphan*/  type; } ;
struct hlsl_ir_deref {TYPE_2__ v; int /*<<< orphan*/  type; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HLSL_IR_DEREF ; 
 int /*<<< orphan*/  HLSL_IR_DEREF_VAR ; 
 struct hlsl_ir_deref* d3dcompiler_alloc (int) ; 

struct hlsl_ir_deref *new_var_deref(struct hlsl_ir_var *var)
{
    struct hlsl_ir_deref *deref = d3dcompiler_alloc(sizeof(*deref));

    if (!deref)
    {
        ERR("Out of memory.\n");
        return NULL;
    }
    deref->node.type = HLSL_IR_DEREF;
    deref->node.data_type = var->data_type;
    deref->type = HLSL_IR_DEREF_VAR;
    deref->v.var = var;
    return deref;
}