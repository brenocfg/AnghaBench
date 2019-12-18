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
struct TYPE_17__ {scalar_t__ uvalue; } ;
struct attribute {TYPE_6__ u; } ;
struct TYPE_18__ {scalar_t__ data; scalar_t__ end_data; int word_size; } ;
typedef  TYPE_7__ dwarf2_traverse_context_t ;
struct TYPE_19__ {TYPE_5__* module; TYPE_1__* sections; } ;
typedef  TYPE_8__ dwarf2_parse_context_t ;
typedef  int /*<<< orphan*/  dwarf2_debug_info_t ;
struct TYPE_16__ {TYPE_4__** format_info; } ;
struct TYPE_14__ {TYPE_2__* dwarf2_info; } ;
struct TYPE_15__ {TYPE_3__ u; } ;
struct TYPE_13__ {int word_size; } ;
struct TYPE_12__ {scalar_t__ address; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_DWARF ; 
 int /*<<< orphan*/  DW_AT_high_pc ; 
 int /*<<< orphan*/  DW_AT_low_pc ; 
 int /*<<< orphan*/  DW_AT_ranges ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ dwarf2_find_attribute (TYPE_8__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct attribute*) ; 
 unsigned long dwarf2_parse_addr (TYPE_7__*) ; 
 size_t section_ranges ; 

__attribute__((used)) static BOOL dwarf2_read_range(dwarf2_parse_context_t* ctx, const dwarf2_debug_info_t* di,
                              unsigned long* plow, unsigned long* phigh)
{
    struct attribute            range;

    if (dwarf2_find_attribute(ctx, di, DW_AT_ranges, &range))
    {
        dwarf2_traverse_context_t   traverse;
        unsigned long               low, high;

        traverse.data = ctx->sections[section_ranges].address + range.u.uvalue;
        traverse.end_data = ctx->sections[section_ranges].address +
            ctx->sections[section_ranges].size;
        traverse.word_size = ctx->module->format_info[DFI_DWARF]->u.dwarf2_info->word_size;

        *plow  = ULONG_MAX;
        *phigh = 0;
        while (traverse.data + 2 * traverse.word_size < traverse.end_data)
        {
            low = dwarf2_parse_addr(&traverse);
            high = dwarf2_parse_addr(&traverse);
            if (low == 0 && high == 0) break;
            if (low == ULONG_MAX) FIXME("unsupported yet (base address selection)\n");
            if (low  < *plow)  *plow = low;
            if (high > *phigh) *phigh = high;
        }
        if (*plow == ULONG_MAX || *phigh == 0) {FIXME("no entry found\n"); return FALSE;}
        if (*plow == *phigh) {FIXME("entry found, but low=high\n"); return FALSE;}

        return TRUE;
    }
    else
    {
        struct attribute            low_pc;
        struct attribute            high_pc;

        if (!dwarf2_find_attribute(ctx, di, DW_AT_low_pc, &low_pc) ||
            !dwarf2_find_attribute(ctx, di, DW_AT_high_pc, &high_pc))
            return FALSE;
        *plow = low_pc.u.uvalue;
        *phigh = high_pc.u.uvalue;
        return TRUE;
    }
}