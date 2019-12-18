#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  offset; int /*<<< orphan*/  kind; } ;
struct TYPE_23__ {TYPE_1__ frame; int /*<<< orphan*/ * func; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_3__ dwarf2_subprogram_t ;
typedef  int /*<<< orphan*/  dwarf2_parse_context_t ;
struct TYPE_24__ {TYPE_2__* abbrev; } ;
typedef  TYPE_4__ dwarf2_debug_info_t ;
struct TYPE_22__ {int tag; int /*<<< orphan*/  entry_code; } ;

/* Variables and functions */
#define  DW_TAG_array_type 146 
#define  DW_TAG_base_type 145 
#define  DW_TAG_class_type 144 
#define  DW_TAG_const_type 143 
#define  DW_TAG_enumeration_type 142 
#define  DW_TAG_imported_declaration 141 
#define  DW_TAG_imported_module 140 
#define  DW_TAG_namespace 139 
#define  DW_TAG_pointer_type 138 
#define  DW_TAG_ptr_to_member_type 137 
#define  DW_TAG_reference_type 136 
#define  DW_TAG_structure_type 135 
#define  DW_TAG_subprogram 134 
#define  DW_TAG_subroutine_type 133 
#define  DW_TAG_typedef 132 
#define  DW_TAG_union_type 131 
#define  DW_TAG_unspecified_type 130 
#define  DW_TAG_variable 129 
#define  DW_TAG_volatile_type 128 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UdtClass ; 
 int /*<<< orphan*/  UdtStruct ; 
 int /*<<< orphan*/  UdtUnion ; 
 int /*<<< orphan*/  Wine_DW_no_register ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf2_parse_array_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_base_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_const_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_enumeration_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_namespace (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_pointer_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_reference_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subroutine_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_typedef (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_udt_type (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_parse_unspecified_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_variable (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf2_parse_volatile_type (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  loc_absolute ; 

__attribute__((used)) static void dwarf2_load_one_entry(dwarf2_parse_context_t* ctx,
                                  dwarf2_debug_info_t* di)
{
    switch (di->abbrev->tag)
    {
    case DW_TAG_typedef:
        dwarf2_parse_typedef(ctx, di);
        break;
    case DW_TAG_base_type:
        dwarf2_parse_base_type(ctx, di);
        break;
    case DW_TAG_pointer_type:
        dwarf2_parse_pointer_type(ctx, di);
        break;
    case DW_TAG_class_type:
        dwarf2_parse_udt_type(ctx, di, UdtClass);
        break;
    case DW_TAG_structure_type:
        dwarf2_parse_udt_type(ctx, di, UdtStruct);
        break;
    case DW_TAG_union_type:
        dwarf2_parse_udt_type(ctx, di, UdtUnion);
        break;
    case DW_TAG_array_type:
        dwarf2_parse_array_type(ctx, di);
        break;
    case DW_TAG_const_type:
        dwarf2_parse_const_type(ctx, di);
        break;
    case DW_TAG_volatile_type:
        dwarf2_parse_volatile_type(ctx, di);
        break;
    case DW_TAG_unspecified_type:
        dwarf2_parse_unspecified_type(ctx, di);
        break;
    case DW_TAG_reference_type:
        dwarf2_parse_reference_type(ctx, di);
        break;
    case DW_TAG_enumeration_type:
        dwarf2_parse_enumeration_type(ctx, di);
        break;
    case DW_TAG_subprogram:
        dwarf2_parse_subprogram(ctx, di);
        break;
    case DW_TAG_subroutine_type:
        dwarf2_parse_subroutine_type(ctx, di);
        break;
    case DW_TAG_variable:
        {
            dwarf2_subprogram_t subpgm;

            subpgm.ctx = ctx;
            subpgm.func = NULL;
            subpgm.frame.kind = loc_absolute;
            subpgm.frame.offset = 0;
            subpgm.frame.reg = Wine_DW_no_register;
            dwarf2_parse_variable(&subpgm, NULL, di);
        }
        break;
    case DW_TAG_namespace:
        dwarf2_parse_namespace(ctx, di);
        break;
    /* silence a couple of C++ defines */
    case DW_TAG_imported_module:
    case DW_TAG_imported_declaration:
    case DW_TAG_ptr_to_member_type:
        break;
    default:
        FIXME("Unhandled Tag type 0x%lx at %s, for %lu\n",
              di->abbrev->tag, dwarf2_debug_ctx(ctx), di->abbrev->entry_code); 
    }
}