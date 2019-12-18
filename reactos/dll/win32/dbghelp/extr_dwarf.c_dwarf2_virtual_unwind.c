#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct module_pair {TYPE_10__* effective; int /*<<< orphan*/  pcs; int /*<<< orphan*/  requested; } ;
struct TYPE_23__ {TYPE_4__* dwarf2_info; } ;
struct module_format {TYPE_5__ u; } ;
struct TYPE_18__ {scalar_t__* rules; } ;
struct frame_info {scalar_t__ ip; size_t retaddr_reg; TYPE_15__ state; int /*<<< orphan*/  lsda_encoding; scalar_t__ aug_z_format; int /*<<< orphan*/  data_align; int /*<<< orphan*/  code_align; } ;
struct cpu_stack_walk {int /*<<< orphan*/  hProcess; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_24__ {unsigned char* data; unsigned char* end_data; int /*<<< orphan*/  word_size; } ;
typedef  TYPE_6__ dwarf2_traverse_context_t ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_21__ {unsigned char* address; int size; } ;
struct TYPE_20__ {unsigned char* address; int size; scalar_t__ rva; } ;
struct TYPE_22__ {int /*<<< orphan*/  word_size; TYPE_3__ debug_frame; TYPE_2__ eh_frame; } ;
struct TYPE_19__ {scalar_t__ BaseOfImage; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* map_dwarf_register ) (size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fetch_regname ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {scalar_t__ reloc_delta; TYPE_1__ module; struct module_format** format_info; } ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_DWARF ; 
 int /*<<< orphan*/  DMT_UNKNOWN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RULE_UNSET ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apply_frame_state (TYPE_10__*,struct cpu_stack_walk*,int /*<<< orphan*/ *,TYPE_15__*,scalar_t__*) ; 
 TYPE_13__* dbghelp_current_cpu ; 
 int /*<<< orphan*/  dwarf2_get_cie (scalar_t__,TYPE_10__*,scalar_t__,TYPE_6__*,TYPE_6__*,struct frame_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf2_leb128_as_unsigned (TYPE_6__*) ; 
 int /*<<< orphan*/  dwarf2_parse_augmentation_ptr (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_cfa_instructions (TYPE_6__*,scalar_t__,struct frame_info*) ; 
 int /*<<< orphan*/  memset (struct frame_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_find_by_addr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_get_debug (struct module_pair*) ; 
 int /*<<< orphan*/  process_find_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (size_t,int /*<<< orphan*/ ) ; 

BOOL dwarf2_virtual_unwind(struct cpu_stack_walk* csw, ULONG_PTR ip, CONTEXT* context, ULONG_PTR* cfa)
{
    struct module_pair pair;
    struct frame_info info;
    dwarf2_traverse_context_t cie_ctx, fde_ctx;
    struct module_format* modfmt;
    const unsigned char* end;
    DWORD_PTR delta;

    if (!(pair.pcs = process_find_by_handle(csw->hProcess)) ||
        !(pair.requested = module_find_by_addr(pair.pcs, ip, DMT_UNKNOWN)) ||
        !module_get_debug(&pair))
        return FALSE;
    modfmt = pair.effective->format_info[DFI_DWARF];
    if (!modfmt) return FALSE;
    memset(&info, 0, sizeof(info));
    fde_ctx.data = modfmt->u.dwarf2_info->eh_frame.address;
    fde_ctx.end_data = fde_ctx.data + modfmt->u.dwarf2_info->eh_frame.size;
    fde_ctx.word_size = modfmt->u.dwarf2_info->word_size;
    /* let offsets relative to the eh_frame sections be correctly computed, as we'll map
     * in this process the IMAGE section at a different address as the one expected by
     * the image
     */
    delta = pair.effective->module.BaseOfImage + modfmt->u.dwarf2_info->eh_frame.rva -
        (DWORD_PTR)modfmt->u.dwarf2_info->eh_frame.address;
    if (!dwarf2_get_cie(ip, pair.effective, delta, &fde_ctx, &cie_ctx, &info, TRUE))
    {
        fde_ctx.data = modfmt->u.dwarf2_info->debug_frame.address;
        fde_ctx.end_data = fde_ctx.data + modfmt->u.dwarf2_info->debug_frame.size;
        fde_ctx.word_size = modfmt->u.dwarf2_info->word_size;
        delta = pair.effective->reloc_delta;
        if (!dwarf2_get_cie(ip, pair.effective, delta, &fde_ctx, &cie_ctx, &info, FALSE))
        {
            TRACE("Couldn't find information for %lx\n", ip);
            return FALSE;
        }
    }

    TRACE("function %lx/%lx code_align %lu data_align %ld retaddr %s\n",
          ip, info.ip, info.code_align, info.data_align,
          dbghelp_current_cpu->fetch_regname(dbghelp_current_cpu->map_dwarf_register(info.retaddr_reg, TRUE)));

    /* if at very beginning of function, return and use default unwinder */
    if (ip == info.ip) return FALSE;
    execute_cfa_instructions(&cie_ctx, ip, &info);

    if (info.aug_z_format)  /* get length of augmentation data */
    {
        ULONG_PTR len = dwarf2_leb128_as_unsigned(&fde_ctx);
        end = fde_ctx.data + len;
    }
    else end = NULL;
    dwarf2_parse_augmentation_ptr(&fde_ctx, info.lsda_encoding); /* handler_data */
    if (end) fde_ctx.data = end;

    execute_cfa_instructions(&fde_ctx, ip, &info);

    /* if there is no information about retaddr, use default unwinder */
    if (info.state.rules[info.retaddr_reg] == RULE_UNSET) return FALSE;

    apply_frame_state(pair.effective, csw, context, &info.state, cfa);

    return TRUE;
}