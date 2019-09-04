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
struct TYPE_3__ {void* seg; void* off; } ;
struct TYPE_4__ {TYPE_1__ ptr; } ;
struct ud_operand {int size; TYPE_2__ lval; void* type; } ;
struct ud {int opr_mode; } ;

/* Variables and functions */
 void* UD_OP_PTR ; 
 void* inp_uint16 (struct ud*) ; 
 void* inp_uint32 (struct ud*) ; 

__attribute__((used)) static void 
decode_a(struct ud* u, struct ud_operand *op)
{
  if (u->opr_mode == 16) {  
    /* seg16:off16 */
    op->type = UD_OP_PTR;
    op->size = 32;
    op->lval.ptr.off = inp_uint16(u);
    op->lval.ptr.seg = inp_uint16(u);
  } else {
    /* seg16:off32 */
    op->type = UD_OP_PTR;
    op->size = 48;
    op->lval.ptr.off = inp_uint32(u);
    op->lval.ptr.seg = inp_uint16(u);
  }
}