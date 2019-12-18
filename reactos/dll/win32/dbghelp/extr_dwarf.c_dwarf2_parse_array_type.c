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
struct symt {int dummy; } ;
struct TYPE_17__ {int uvalue; } ;
struct attribute {TYPE_2__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/  module; struct symt** symt_cache; } ;
typedef  TYPE_3__ dwarf2_parse_context_t ;
struct TYPE_19__ {struct symt* symt; TYPE_1__* abbrev; } ;
typedef  TYPE_4__ dwarf2_debug_info_t ;
struct TYPE_20__ {struct symt symt; } ;
struct TYPE_16__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_count ; 
 int /*<<< orphan*/  DW_AT_lower_bound ; 
 int /*<<< orphan*/  DW_AT_upper_bound ; 
#define  DW_TAG_subrange_type 128 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,struct attribute*) ; 
 struct vector* dwarf2_get_di_children (TYPE_3__*,TYPE_4__*) ; 
 struct symt* dwarf2_lookup_type (TYPE_3__*,TYPE_4__*) ; 
 size_t sc_int4 ; 
 TYPE_5__* symt_new_array (int /*<<< orphan*/ ,int,int,struct symt*,struct symt*) ; 
 scalar_t__ vector_at (struct vector const*,unsigned int) ; 
 unsigned int vector_length (struct vector const*) ; 

__attribute__((used)) static struct symt* dwarf2_parse_array_type(dwarf2_parse_context_t* ctx,
                                            dwarf2_debug_info_t* di)
{
    struct symt* ref_type;
    struct symt* idx_type = NULL;
    struct attribute min, max, cnt;
    dwarf2_debug_info_t* child;
    unsigned int i;
    const struct vector* children;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));

    ref_type = dwarf2_lookup_type(ctx, di);

    if (!(children = dwarf2_get_di_children(ctx, di)))
    {
        /* fake an array with unknown size */
        /* FIXME: int4 even on 64bit machines??? */
        idx_type = ctx->symt_cache[sc_int4];
        min.u.uvalue = 0;
        max.u.uvalue = -1;
    }
    else for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);
        switch (child->abbrev->tag)
        {
        case DW_TAG_subrange_type:
            idx_type = dwarf2_lookup_type(ctx, child);
            if (!dwarf2_find_attribute(ctx, child, DW_AT_lower_bound, &min))
                min.u.uvalue = 0;
            if (!dwarf2_find_attribute(ctx, child, DW_AT_upper_bound, &max))
                max.u.uvalue = 0;
            if (dwarf2_find_attribute(ctx, child, DW_AT_count, &cnt))
                max.u.uvalue = min.u.uvalue + cnt.u.uvalue;
            break;
        default:
            FIXME("Unhandled Tag type 0x%lx at %s, for %s\n",
                  child->abbrev->tag, dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));
            break;
        }
    }
    di->symt = &symt_new_array(ctx->module, min.u.uvalue, max.u.uvalue, ref_type, idx_type)->symt;
    return di->symt;
}