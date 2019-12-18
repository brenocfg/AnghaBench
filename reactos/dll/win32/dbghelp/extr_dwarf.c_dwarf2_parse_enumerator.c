#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct symt_enum {int dummy; } ;
struct TYPE_7__ {scalar_t__ svalue; int /*<<< orphan*/  string; } ;
struct attribute {TYPE_1__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ dwarf2_parse_context_t ;
typedef  int /*<<< orphan*/  dwarf2_debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_const_value ; 
 int /*<<< orphan*/  DW_AT_name ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct attribute*) ; 
 scalar_t__ dwarf2_get_di_children (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symt_add_enum_element (int /*<<< orphan*/ ,struct symt_enum*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dwarf2_parse_enumerator(dwarf2_parse_context_t* ctx,
                                    dwarf2_debug_info_t* di,
                                    struct symt_enum* parent)
{
    struct attribute    name;
    struct attribute    value;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di)); 

    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name)) return;
    if (!dwarf2_find_attribute(ctx, di, DW_AT_const_value, &value)) value.u.svalue = 0;
    symt_add_enum_element(ctx->module, parent, name.u.string, value.u.svalue);

    if (dwarf2_get_di_children(ctx, di)) FIXME("Unsupported children\n");
}