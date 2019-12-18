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
struct list {int dummy; } ;
struct TYPE_3__ {struct list* elements; } ;
struct hlsl_type {char const* name; int dimx; int dimy; int /*<<< orphan*/  entry; TYPE_1__ e; int /*<<< orphan*/  modifiers; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  types; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HLSL_CLASS_STRUCT ; 
 struct hlsl_type* d3dcompiler_alloc (int) ; 
 TYPE_2__ hlsl_ctx ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hlsl_type *new_struct_type(const char *name, DWORD modifiers, struct list *fields)
{
    struct hlsl_type *type = d3dcompiler_alloc(sizeof(*type));

    if (!type)
    {
        ERR("Out of memory.\n");
        return NULL;
    }
    type->type = HLSL_CLASS_STRUCT;
    type->name = name;
    type->dimx = type->dimy = 1;
    type->modifiers = modifiers;
    type->e.elements = fields;

    list_add_tail(&hlsl_ctx.types, &type->entry);

    return type;
}