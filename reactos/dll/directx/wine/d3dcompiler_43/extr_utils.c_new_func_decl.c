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
struct list {int dummy; } ;
struct hlsl_type {int dummy; } ;
struct hlsl_ir_function_decl {struct list* parameters; struct hlsl_type* return_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
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
    decl->return_type = return_type;
    decl->parameters = parameters;

    return decl;
}