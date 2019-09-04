#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct asm_parser {int /*<<< orphan*/  status; TYPE_1__* shader; int /*<<< orphan*/  line_no; } ;
struct TYPE_2__ {scalar_t__ version; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERPS_VERSION (int,int /*<<< orphan*/ ) ; 
 scalar_t__ BWRITERSPDM_MSAMPCENTROID ; 
 scalar_t__ BWRITERSPDM_PARTIALPRECISION ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_sampler (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_dcl_sampler(struct asm_parser *This, DWORD samptype,
                                  DWORD mod, DWORD regnum,
                                  unsigned int line_no) {
    if(!This->shader) return;
    if(mod != 0 &&
       (This->shader->version != BWRITERPS_VERSION(3, 0) ||
        (mod != BWRITERSPDM_MSAMPCENTROID &&
         mod != BWRITERSPDM_PARTIALPRECISION))) {
        asmparser_message(This, "Line %u: Unsupported modifier in dcl instruction\n", This->line_no);
        set_parse_status(&This->status, PARSE_ERR);
        return;
    }
    if(!record_sampler(This->shader, samptype, mod, regnum)) {
        ERR("Out of memory\n");
        set_parse_status(&This->status, PARSE_ERR);
    }
}