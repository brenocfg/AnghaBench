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
struct instruction {unsigned int num_srcs; int /*<<< orphan*/ * src; int /*<<< orphan*/  predicate; scalar_t__ has_predicate; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* srcreg ) (struct bc_writer*,int /*<<< orphan*/ *,struct bytecode_buffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bc_writer*,int /*<<< orphan*/ *,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct bc_writer*,int /*<<< orphan*/ *,struct bytecode_buffer*) ; 

__attribute__((used)) static void write_srcregs(struct bc_writer *This, const struct instruction *instr,
                          struct bytecode_buffer *buffer){
    unsigned int i;
    if(instr->has_predicate){
        This->funcs->srcreg(This, &instr->predicate, buffer);
    }
    for(i = 0; i < instr->num_srcs; i++){
        This->funcs->srcreg(This, &instr->src[i], buffer);
    }
}