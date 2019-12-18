#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct symt {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ dwarf2_parse_context_t ;
struct TYPE_13__ {struct symt* symt; } ;
typedef  TYPE_2__ dwarf2_debug_info_t ;
struct TYPE_14__ {struct symt symt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_2__*) ; 
 scalar_t__ dwarf2_get_di_children (TYPE_1__*,TYPE_2__*) ; 
 struct symt* dwarf2_lookup_type (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* symt_new_pointer (int /*<<< orphan*/ ,struct symt*,int) ; 

__attribute__((used)) static struct symt* dwarf2_parse_reference_type(dwarf2_parse_context_t* ctx,
                                                dwarf2_debug_info_t* di)
{
    struct symt* ref_type = NULL;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));

    ref_type = dwarf2_lookup_type(ctx, di);
    /* FIXME: for now, we hard-wire C++ references to pointers */
    di->symt = &symt_new_pointer(ctx->module, ref_type, sizeof(void *))->symt;

    if (dwarf2_get_di_children(ctx, di)) FIXME("Unsupported children\n");

    return di->symt;
}