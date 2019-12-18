#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct symt_udt {int dummy; } ;
struct symt {int dummy; } ;
struct TYPE_26__ {char* string; scalar_t__ uvalue; } ;
struct attribute {TYPE_1__ u; } ;
typedef  enum UdtKind { ____Placeholder_UdtKind } UdtKind ;
struct TYPE_28__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_3__ dwarf2_parse_context_t ;
struct TYPE_29__ {struct symt* symt; TYPE_2__* abbrev; } ;
typedef  TYPE_4__ dwarf2_debug_info_t ;
struct TYPE_30__ {struct symt symt; } ;
struct TYPE_27__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_byte_size ; 
 int /*<<< orphan*/  DW_AT_name ; 
#define  DW_TAG_GNU_formal_parameter_pack 144 
#define  DW_TAG_GNU_template_parameter_pack 143 
#define  DW_TAG_array_type 142 
#define  DW_TAG_class_type 141 
#define  DW_TAG_const_type 140 
#define  DW_TAG_enumeration_type 139 
#define  DW_TAG_imported_declaration 138 
#define  DW_TAG_inheritance 137 
#define  DW_TAG_member 136 
#define  DW_TAG_ptr_to_member_type 135 
#define  DW_TAG_structure_type 134 
#define  DW_TAG_subprogram 133 
#define  DW_TAG_template_type_param 132 
#define  DW_TAG_template_value_param 131 
#define  DW_TAG_typedef 130 
#define  DW_TAG_union_type 129 
#define  DW_TAG_variable 128 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,struct attribute*) ; 
 int /*<<< orphan*/  dwarf2_get_cpp_name (TYPE_3__*,TYPE_4__*,char*) ; 
 struct vector* dwarf2_get_di_children (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_array_type (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_const_type (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_enumeration_type (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_udt_member (TYPE_3__*,TYPE_4__*,struct symt_udt*) ; 
 TYPE_5__* symt_new_udt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ vector_at (struct vector*,unsigned int) ; 
 unsigned int vector_length (struct vector*) ; 

__attribute__((used)) static struct symt* dwarf2_parse_udt_type(dwarf2_parse_context_t* ctx,
                                          dwarf2_debug_info_t* di,
                                          enum UdtKind udt)
{
    struct attribute    name;
    struct attribute    size;
    struct vector*      children;
    dwarf2_debug_info_t*child;
    unsigned int        i;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di)); 

    /* quirk... FIXME provide real support for anonymous UDTs */
    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name))
        name.u.string = "zz_anon_zz";
    if (!dwarf2_find_attribute(ctx, di, DW_AT_byte_size, &size)) size.u.uvalue = 0;

    di->symt = &symt_new_udt(ctx->module, dwarf2_get_cpp_name(ctx, di, name.u.string),
                             size.u.uvalue, udt)->symt;

    children = dwarf2_get_di_children(ctx, di);
    if (children) for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);

        switch (child->abbrev->tag)
        {
        case DW_TAG_array_type:
            dwarf2_parse_array_type(ctx, di);
            break;
        case DW_TAG_member:
            /* FIXME: should I follow the sibling stuff ?? */
            dwarf2_parse_udt_member(ctx, child, (struct symt_udt*)di->symt);
            break;
        case DW_TAG_enumeration_type:
            dwarf2_parse_enumeration_type(ctx, child);
            break;
        case DW_TAG_subprogram:
            dwarf2_parse_subprogram(ctx, child);
            break;
        case DW_TAG_const_type:
            dwarf2_parse_const_type(ctx, child);
            break;
        case DW_TAG_structure_type:
        case DW_TAG_class_type:
        case DW_TAG_union_type:
        case DW_TAG_typedef:
            /* FIXME: we need to handle nested udt definitions */
        case DW_TAG_inheritance:
        case DW_TAG_template_type_param:
        case DW_TAG_template_value_param:
        case DW_TAG_variable:
        case DW_TAG_imported_declaration:
        case DW_TAG_ptr_to_member_type:
        case DW_TAG_GNU_template_parameter_pack:
        case DW_TAG_GNU_formal_parameter_pack:
            /* FIXME: some C++ related stuff */
            break;
        default:
            FIXME("Unhandled Tag type 0x%lx at %s, for %s\n",
                  child->abbrev->tag, dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));
            break;
        }
    }

    return di->symt;
}