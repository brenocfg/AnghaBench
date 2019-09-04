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
struct TYPE_5__ {int /*<<< orphan*/  record; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; int /*<<< orphan*/  array; } ;
struct TYPE_6__ {TYPE_2__ record; TYPE_1__ array; } ;
struct hlsl_ir_deref {int type; TYPE_3__ v; } ;

/* Variables and functions */
#define  HLSL_IR_DEREF_ARRAY 130 
#define  HLSL_IR_DEREF_RECORD 129 
#define  HLSL_IR_DEREF_VAR 128 
 int /*<<< orphan*/  d3dcompiler_free (struct hlsl_ir_deref*) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ir_deref(struct hlsl_ir_deref *deref)
{
    switch (deref->type)
    {
        case HLSL_IR_DEREF_VAR:
            /* Variables are shared among nodes in the tree. */
            break;
        case HLSL_IR_DEREF_ARRAY:
            free_instr(deref->v.array.array);
            free_instr(deref->v.array.index);
            break;
        case HLSL_IR_DEREF_RECORD:
            free_instr(deref->v.record.record);
            break;
    }
    d3dcompiler_free(deref);
}