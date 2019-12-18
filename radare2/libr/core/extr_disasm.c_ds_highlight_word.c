#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* opstr; char* color_linehl; int /*<<< orphan*/  asmop; } ;
typedef  TYPE_1__ RDisasmState ;

/* Variables and functions */
 char* Color_RESET_BG ; 
 scalar_t__ line_highlighted (TYPE_1__*) ; 
 char* r_asm_op_get_asm (int /*<<< orphan*/ *) ; 
 char* r_str_highlight (char*,char*,char*,char const*) ; 

__attribute__((used)) static void ds_highlight_word(RDisasmState * ds, char *word, char *color) {
	char *source = ds->opstr? ds->opstr: r_asm_op_get_asm (&ds->asmop);
	const char *color_reset = line_highlighted (ds) ? ds->color_linehl : Color_RESET_BG;
	char *asm_str = r_str_highlight (source, word, color, color_reset);
	ds->opstr = asm_str? asm_str: source;
}