#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct symt_enum {int dummy; } ;
struct symt_basic {int /*<<< orphan*/  symt; } ;
struct symt {int dummy; } ;
struct TYPE_16__ {int uvalue; int /*<<< orphan*/ * string; } ;
struct attribute {TYPE_1__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_3__ dwarf2_parse_context_t ;
struct TYPE_19__ {struct symt* symt; TYPE_2__* abbrev; } ;
typedef  TYPE_4__ dwarf2_debug_info_t ;
struct TYPE_20__ {struct symt symt; } ;
struct TYPE_17__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_byte_size ; 
 int /*<<< orphan*/  DW_AT_name ; 
#define  DW_TAG_enumerator 128 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btInt ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,struct attribute*) ; 
 struct vector* dwarf2_get_di_children (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_enumerator (TYPE_3__*,TYPE_4__*,struct symt_enum*) ; 
 struct symt_basic* symt_new_basic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_5__* symt_new_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vector_at (struct vector*,unsigned int) ; 
 unsigned int vector_length (struct vector*) ; 

__attribute__((used)) static struct symt* dwarf2_parse_enumeration_type(dwarf2_parse_context_t* ctx,
                                                  dwarf2_debug_info_t* di)
{
    struct attribute    name;
    struct attribute    size;
    struct symt_basic*  basetype;
    struct vector*      children;
    dwarf2_debug_info_t*child;
    unsigned int        i;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di)); 

    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name)) name.u.string = NULL;
    if (!dwarf2_find_attribute(ctx, di, DW_AT_byte_size, &size)) size.u.uvalue = 4;

    switch (size.u.uvalue) /* FIXME: that's wrong */
    {
    case 1: basetype = symt_new_basic(ctx->module, btInt, "char", 1); break;
    case 2: basetype = symt_new_basic(ctx->module, btInt, "short", 2); break;
    default:
    case 4: basetype = symt_new_basic(ctx->module, btInt, "int", 4); break;
    }

    di->symt = &symt_new_enum(ctx->module, name.u.string, &basetype->symt)->symt;

    children = dwarf2_get_di_children(ctx, di);
    /* FIXME: should we use the sibling stuff ?? */
    if (children) for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);

        switch (child->abbrev->tag)
        {
        case DW_TAG_enumerator:
            dwarf2_parse_enumerator(ctx, child, (struct symt_enum*)di->symt);
            break;
        default:
            FIXME("Unhandled Tag type 0x%lx at %s, for %s\n",
                  di->abbrev->tag, dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));
	}
    }
    return di->symt;
}