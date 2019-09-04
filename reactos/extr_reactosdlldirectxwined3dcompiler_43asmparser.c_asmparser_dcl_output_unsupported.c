#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct shader_reg {int dummy; } ;
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  line_no; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_dcl_output_unsupported(struct asm_parser *This, DWORD usage, DWORD num,
                                             const struct shader_reg *reg) {
    asmparser_message(This, "Line %u: Output declaration unsupported in this shader version\n", This->line_no);
    set_parse_status(&This->status, PARSE_ERR);
}