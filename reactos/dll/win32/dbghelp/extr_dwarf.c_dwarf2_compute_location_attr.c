#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct location {scalar_t__ kind; int reg; unsigned long offset; } ;
struct TYPE_16__ {int size; int ptr; } ;
struct TYPE_17__ {unsigned long uvalue; TYPE_5__ block; } ;
struct attribute {int form; TYPE_6__ u; } ;
typedef  enum location_error { ____Placeholder_location_error } location_error ;
struct TYPE_18__ {int data; int end_data; int /*<<< orphan*/  word_size; } ;
typedef  TYPE_7__ dwarf2_traverse_context_t ;
struct TYPE_19__ {TYPE_4__* module; } ;
typedef  TYPE_8__ dwarf2_parse_context_t ;
typedef  int /*<<< orphan*/  dwarf2_debug_info_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; TYPE_3__** format_info; } ;
struct TYPE_13__ {TYPE_1__* dwarf2_info; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  word_size; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_DWARF ; 
#define  DW_FORM_block 137 
#define  DW_FORM_block1 136 
#define  DW_FORM_block2 135 
#define  DW_FORM_block4 134 
#define  DW_FORM_data1 133 
#define  DW_FORM_data2 132 
#define  DW_FORM_data4 131 
#define  DW_FORM_data8 130 
#define  DW_FORM_sdata 129 
#define  DW_FORM_udata 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int Wine_DW_no_register ; 
 int compute_location (TYPE_7__*,struct location*,int /*<<< orphan*/ *,struct location const*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_8__*,int /*<<< orphan*/  const*,unsigned long,struct attribute*) ; 
 scalar_t__ loc_absolute ; 
 scalar_t__ loc_dwarf2_block ; 
 scalar_t__ loc_dwarf2_location_list ; 
 scalar_t__ loc_error ; 
 int /*<<< orphan*/  memcpy (unsigned int*,int,unsigned int) ; 
 unsigned int* pool_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL dwarf2_compute_location_attr(dwarf2_parse_context_t* ctx,
                                         const dwarf2_debug_info_t* di,
                                         unsigned long dw,
                                         struct location* loc,
                                         const struct location* frame)
{
    struct attribute xloc;

    if (!dwarf2_find_attribute(ctx, di, dw, &xloc)) return FALSE;

    switch (xloc.form)
    {
    case DW_FORM_data1: case DW_FORM_data2:
    case DW_FORM_udata: case DW_FORM_sdata:
        loc->kind = loc_absolute;
        loc->reg = 0;
        loc->offset = xloc.u.uvalue;
        return TRUE;
    case DW_FORM_data4: case DW_FORM_data8:
        loc->kind = loc_dwarf2_location_list;
        loc->reg = Wine_DW_no_register;
        loc->offset = xloc.u.uvalue;
        return TRUE;
    case DW_FORM_block:
    case DW_FORM_block1:
    case DW_FORM_block2:
    case DW_FORM_block4:
        break;
    default: FIXME("Unsupported yet form %lx\n", xloc.form);
        return FALSE;
    }

    /* assume we have a block form */

    if (xloc.u.block.size)
    {
        dwarf2_traverse_context_t       lctx;
        enum location_error             err;

        lctx.data = xloc.u.block.ptr;
        lctx.end_data = xloc.u.block.ptr + xloc.u.block.size;
        lctx.word_size = ctx->module->format_info[DFI_DWARF]->u.dwarf2_info->word_size;

        err = compute_location(&lctx, loc, NULL, frame);
        if (err < 0)
        {
            loc->kind = loc_error;
            loc->reg = err;
        }
        else if (loc->kind == loc_dwarf2_block)
        {
            unsigned*   ptr = pool_alloc(&ctx->module->pool,
                                         sizeof(unsigned) + xloc.u.block.size);
            *ptr = xloc.u.block.size;
            memcpy(ptr + 1, xloc.u.block.ptr, xloc.u.block.size);
#ifndef __REACTOS__
            loc->offset = (unsigned long)ptr;
#else
            loc->offset = (uintptr_t)ptr;
#endif
        }
    }
    return TRUE;
}