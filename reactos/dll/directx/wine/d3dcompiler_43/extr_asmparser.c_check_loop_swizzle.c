#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ swizzle; } ;
struct shader_reg {scalar_t__ type; TYPE_2__* rel_reg; TYPE_1__ u; } ;
struct asm_parser {int /*<<< orphan*/  status; int /*<<< orphan*/  line_no; } ;
struct TYPE_6__ {scalar_t__ swizzle; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_LOOP ; 
 scalar_t__ BWRITERVS_NOSWIZZLE ; 
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_loop_swizzle(struct asm_parser *This,
                               const struct shader_reg *src) {
    if((src->type == BWRITERSPR_LOOP && src->u.swizzle != BWRITERVS_NOSWIZZLE) ||
       (src->rel_reg && src->rel_reg->type == BWRITERSPR_LOOP &&
        src->rel_reg->u.swizzle != BWRITERVS_NOSWIZZLE)) {
        asmparser_message(This, "Line %u: Swizzle not allowed on aL register\n", This->line_no);
        set_parse_status(&This->status, PARSE_ERR);
    }
}