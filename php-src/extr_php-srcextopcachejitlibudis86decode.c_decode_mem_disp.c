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
struct TYPE_2__ {int /*<<< orphan*/  uqword; int /*<<< orphan*/  udword; int /*<<< orphan*/  uword; int /*<<< orphan*/  ubyte; } ;
struct ud_operand {int offset; TYPE_1__ lval; } ;
struct ud {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inp_uint16 (struct ud*) ; 
 int /*<<< orphan*/  inp_uint32 (struct ud*) ; 
 int /*<<< orphan*/  inp_uint64 (struct ud*) ; 
 int /*<<< orphan*/  inp_uint8 (struct ud*) ; 

__attribute__((used)) static void 
decode_mem_disp(struct ud* u, unsigned int size, struct ud_operand *op)
{
  switch (size) {
  case 8:
    op->offset = 8; 
    op->lval.ubyte  = inp_uint8(u);
    break;
  case 16:
    op->offset = 16; 
    op->lval.uword  = inp_uint16(u); 
    break;
  case 32:
    op->offset = 32; 
    op->lval.udword = inp_uint32(u); 
    break;
  case 64:
    op->offset = 64; 
    op->lval.uqword = inp_uint64(u); 
    break;
  default:
      return;
  }
}