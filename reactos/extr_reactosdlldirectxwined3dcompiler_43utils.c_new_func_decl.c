#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct hlsl_type {int dummy; } ;
struct TYPE_2__ {struct hlsl_type* data_type; int /*<<< orphan*/  type; } ;
struct hlsl_ir_function_decl {struct list* parameters; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HLSL_IR_FUNCTION_DECL ; 
 struct hlsl_ir_function_decl* d3dcompiler_alloc (int) ; 

struct hlsl_ir_function_decl *new_func_decl(struct hlsl_type *return_type, struct list *parameters)
{
    struct hlsl_ir_function_decl *decl;

    decl = d3dcompiler_alloc(sizeof(*decl));
    if (!decl)
    {
        ERR("Out of memory.\n");
        return NULL;
    }
    decl->node.type = HLSL_IR_FUNCTION_DECL;
    decl->node.data_type = return_type;
    decl->parameters = parameters;

    return decl;
}