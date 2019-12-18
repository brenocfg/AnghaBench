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
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  line_no; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSPSM_BIAS ; 
 scalar_t__ BWRITERSPSM_BIASNEG ; 
 scalar_t__ BWRITERSPSM_COMP ; 
 scalar_t__ BWRITERSPSM_DW ; 
 scalar_t__ BWRITERSPSM_DZ ; 
 scalar_t__ BWRITERSPSM_SIGN ; 
 scalar_t__ BWRITERSPSM_SIGNNEG ; 
 scalar_t__ BWRITERSPSM_X2 ; 
 scalar_t__ BWRITERSPSM_X2NEG ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_print_srcmod (scalar_t__) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_legacy_srcmod(struct asm_parser *This, DWORD srcmod) {
    if(srcmod == BWRITERSPSM_BIAS || srcmod == BWRITERSPSM_BIASNEG ||
       srcmod == BWRITERSPSM_SIGN || srcmod == BWRITERSPSM_SIGNNEG ||
       srcmod == BWRITERSPSM_COMP || srcmod == BWRITERSPSM_X2 ||
       srcmod == BWRITERSPSM_X2NEG || srcmod == BWRITERSPSM_DZ ||
       srcmod == BWRITERSPSM_DW) {
        asmparser_message(This, "Line %u: Source modifier %s not supported in this shader version\n",
                          This->line_no,
                          debug_print_srcmod(srcmod));
        set_parse_status(&This->status, PARSE_ERR);
    }
}