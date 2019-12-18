#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  config; TYPE_1__* print; int /*<<< orphan*/  printidx; } ;
struct TYPE_10__ {int /*<<< orphan*/  dumpCols; int /*<<< orphan*/  cols; int /*<<< orphan*/  asm_cmt_col; int /*<<< orphan*/  asm_indent; int /*<<< orphan*/  asm_bytes; int /*<<< orphan*/  asm_instr; int /*<<< orphan*/  asm_offset; int /*<<< orphan*/  current5format; int /*<<< orphan*/  current4format; int /*<<< orphan*/  current3format; int /*<<< orphan*/  printMode; int /*<<< orphan*/  hexMode; int /*<<< orphan*/  disMode; int /*<<< orphan*/  ocur; int /*<<< orphan*/  cur; int /*<<< orphan*/  cur_enabled; int /*<<< orphan*/  printidx; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int /*<<< orphan*/  ocur; int /*<<< orphan*/  cur; int /*<<< orphan*/  cur_enabled; } ;
typedef  TYPE_2__ RCoreVisualTab ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 size_t PRINT_3_FORMATS ; 
 size_t PRINT_4_FORMATS ; 
 size_t PRINT_5_FORMATS ; 
 size_t PRINT_HEX_FORMATS ; 
 size_t R_ABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current3format ; 
 int /*<<< orphan*/  current4format ; 
 int /*<<< orphan*/  current5format ; 
 int /*<<< orphan*/  disMode ; 
 int /*<<< orphan*/  hexMode ; 
 int /*<<< orphan*/ * print3Formats ; 
 int /*<<< orphan*/ * print4Formats ; 
 int /*<<< orphan*/ * print5Formats ; 
 int /*<<< orphan*/ * printHexFormats ; 
 int /*<<< orphan*/  printMode ; 
 int /*<<< orphan*/ * printfmtSingle ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_visual_applyDisMode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_applyHexMode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_if_fail (int) ; 

__attribute__((used)) static void visual_tabset(RCore *core, RCoreVisualTab *tab) {
	r_return_if_fail (core && tab);

	r_core_seek (core, tab->offset, 1);
	core->printidx = tab->printidx;
	core->print->cur_enabled = tab->cur_enabled;
	core->print->cur = tab->cur;
	core->print->ocur = tab->ocur;
	disMode = tab->disMode;
	hexMode = tab->hexMode;
	printMode = tab->printMode;
	current3format = tab->current3format;
	current4format = tab->current4format;
	current5format = tab->current5format;
	r_core_visual_applyDisMode (core, disMode);
	r_core_visual_applyHexMode (core, hexMode);
	r_config_set_i (core->config, "asm.offset", tab->asm_offset);
	r_config_set_i (core->config, "asm.instr", tab->asm_instr);
	r_config_set_i (core->config, "asm.bytes", tab->asm_bytes);
	r_config_set_i (core->config, "asm.indent", tab->asm_indent);
	r_config_set_i (core->config, "asm.cmt.col", tab->asm_cmt_col);
	r_config_set_i (core->config, "hex.cols", tab->cols);
	r_config_set_i (core->config, "scr.dumpcols", tab->dumpCols);
	printfmtSingle[0] = printHexFormats[R_ABS(hexMode) % PRINT_HEX_FORMATS];
	printfmtSingle[2] = print3Formats[R_ABS(current3format) % PRINT_3_FORMATS];
	printfmtSingle[3] = print4Formats[R_ABS(current4format) % PRINT_4_FORMATS];
	printfmtSingle[4] = print5Formats[R_ABS(current5format) % PRINT_5_FORMATS];
}