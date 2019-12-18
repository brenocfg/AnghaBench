#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  enc; scalar_t__ map; } ;
typedef  TYPE_1__ hexagon_opcode ;
typedef  int hexagon_insn ;

/* Variables and functions */
 TYPE_1__* HEXAGON_CODE_NEXT_DIS (TYPE_1__ const*) ; 
 int HEXAGON_END_PACKET_RESET (int) ; 
 int hexagon_encode_mask (int /*<<< orphan*/ ) ; 
 int hexagon_encode_opcode (int /*<<< orphan*/ ) ; 
 TYPE_1__* hexagon_opcode_lookup_dis (int) ; 

const hexagon_opcode *
hexagon_lookup_insn
(hexagon_insn insn)
{
  const hexagon_opcode *opcode;
  hexagon_insn encode;
  hexagon_insn mask;

  /* Reset the packet bits. */
  insn = HEXAGON_END_PACKET_RESET (insn);

  for (opcode = hexagon_opcode_lookup_dis (insn);
       opcode;
       opcode = HEXAGON_CODE_NEXT_DIS (opcode))
    {
      if (opcode->map)
        continue;

      encode = hexagon_encode_opcode (opcode->enc);
      mask   = hexagon_encode_mask   (opcode->enc);

      if ((insn & mask) == (encode & mask))
        return (opcode);
    }

  return NULL;
}