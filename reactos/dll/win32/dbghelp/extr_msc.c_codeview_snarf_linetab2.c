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
struct TYPE_3__ {int tag; } ;
struct symt_function {TYPE_1__ symt; } ;
struct msc_debug_info {int /*<<< orphan*/  module; } ;
struct codeview_lt2blk_lines {unsigned int nlines; TYPE_2__* l; int /*<<< orphan*/  start; int /*<<< orphan*/  seg; int /*<<< orphan*/  file_offset; int /*<<< orphan*/  size; } ;
struct codeview_linetab2_file {int /*<<< orphan*/  offset; } ;
struct codeview_linetab2 {int header; int size_of_block; } ;
struct TYPE_4__ {int lineno; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  LT2_FILES_BLOCK 129 
#define  LT2_LINES_BLOCK 128 
 int SymTagFunction ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codeview_get_address (struct msc_debug_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct codeview_linetab2* codeview_linetab2_next_block (struct codeview_linetab2 const*) ; 
 unsigned int source_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  symt_add_func_line (int /*<<< orphan*/ ,struct symt_function*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ symt_find_nearest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void codeview_snarf_linetab2(const struct msc_debug_info* msc_dbg, const BYTE* linetab, DWORD size,
                                    const char* strimage, DWORD strsize)
{
    unsigned    i;
    DWORD_PTR       addr;
    const struct codeview_linetab2*     lt2;
    const struct codeview_linetab2*     lt2_files = NULL;
    const struct codeview_lt2blk_lines* lines_blk;
    const struct codeview_linetab2_file*fd;
    unsigned    source;
    struct symt_function* func;

    /* locate LT2_FILES_BLOCK (if any) */
    lt2 = (const struct codeview_linetab2*)linetab;
    while ((const BYTE*)(lt2 + 1) < linetab + size)
    {
        if (lt2->header == LT2_FILES_BLOCK)
        {
            lt2_files = lt2;
            break;
        }
        lt2 = codeview_linetab2_next_block(lt2);
    }
    if (!lt2_files)
    {
        TRACE("No LT2_FILES_BLOCK found\n");
        return;
    }

    lt2 = (const struct codeview_linetab2*)linetab;
    while ((const BYTE*)(lt2 + 1) < linetab + size)
    {
        /* FIXME: should also check that whole lines_blk fits in linetab + size */
        switch (lt2->header)
        {
        case LT2_LINES_BLOCK:
            /* Skip blocks that are too small - Intel C Compiler generates these. */
            if (lt2->size_of_block < sizeof (struct codeview_lt2blk_lines)) break;
            lines_blk = (const struct codeview_lt2blk_lines*)lt2;
            /* FIXME: should check that file_offset is within the LT2_FILES_BLOCK we've seen */
            addr = codeview_get_address(msc_dbg, lines_blk->seg, lines_blk->start);
            TRACE("block from %04x:%08x #%x (%x lines)\n",
                  lines_blk->seg, lines_blk->start, lines_blk->size, lines_blk->nlines);
            fd = (const struct codeview_linetab2_file*)((const char*)lt2_files + 8 + lines_blk->file_offset);
            /* FIXME: should check that string is within strimage + strsize */
            source = source_new(msc_dbg->module, NULL, strimage + fd->offset);
            func = (struct symt_function*)symt_find_nearest(msc_dbg->module, addr);
            /* FIXME: at least labels support line numbers */
            if (!func || func->symt.tag != SymTagFunction)
            {
                WARN("--not a func at %04x:%08x %lx tag=%d\n",
                     lines_blk->seg, lines_blk->start, addr, func ? func->symt.tag : -1);
                break;
            }
            for (i = 0; i < lines_blk->nlines; i++)
            {
                symt_add_func_line(msc_dbg->module, func, source,
                                   lines_blk->l[i].lineno ^ 0x80000000,
                                   lines_blk->l[i].offset);
            }
            break;
        case LT2_FILES_BLOCK: /* skip */
            break;
        default:
            TRACE("Block end %x\n", lt2->header);
            lt2 = (const struct codeview_linetab2*)((const char*)linetab + size);
            continue;
        }
        lt2 = codeview_linetab2_next_block(lt2);
    }
}