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
typedef  int uint8_t ;
struct ud {int pfx_str; int pfx_opr; TYPE_1__* le; } ;
struct TYPE_2__ {scalar_t__* table; } ;

/* Variables and functions */
 int decode_ext (struct ud*,scalar_t__) ; 

__attribute__((used)) static int
decode_ssepfx(struct ud *u)
{
  uint8_t idx;
  uint8_t pfx;
 
  /*
   * String prefixes (f2, f3) take precedence over operand
   * size prefix (66).
   */
  pfx = u->pfx_str;
  if (pfx == 0) {
    pfx = u->pfx_opr;
  }
  idx = ((pfx & 0xf) + 1) / 2;
  if (u->le->table[idx] == 0) {
    idx = 0;
  }
  if (idx && u->le->table[idx] != 0) {
    /*
     * "Consume" the prefix as a part of the opcode, so it is no
     * longer exported as an instruction prefix.
     */
    u->pfx_str = 0;
    if (pfx == 0x66) {
        /* 
         * consume "66" only if it was used for decoding, leaving
         * it to be used as an operands size override for some
         * simd instructions.
         */
        u->pfx_opr = 0;
    }
  }
  return decode_ext(u, u->le->table[idx]);
}